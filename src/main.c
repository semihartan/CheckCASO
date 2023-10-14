#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <ntstatus.h>
#include <d3dkmthk.h>
 
#define MORE_INFO_MESSAGE L" Look at the documentation for more information about what this tier level means.\n"

#pragma comment(lib, "gdi32.lib")
  
D3DKMT_ENUMADAPTERS g_enumAdapters;
D3DKMT_QUERYADAPTERINFO g_queryAdapterInfo;
D3DKMT_DRIVER_DESCRIPTION g_driverDescription;
int g_graphicsAdapterIndex = 0;
bool g_lookedUpIndices[MAX_ENUM_ADAPTERS] = { false };

int wmain()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	 
	NTSTATUS ntstatus = STATUS_SUCCESS;
	D3DKMT_HANDLE adapterHandle;
	WCHAR answer = L'\0';
	ntstatus = D3DKMTEnumAdapters(&g_enumAdapters);
	if (ntstatus != STATUS_SUCCESS)
	{
		wprintf(L"Failed to enumerate the adapter.\n");
		return -1;
	}
	if (g_enumAdapters.NumAdapters == 0)
	{
		wprintf(L"There is no any available graphics adapter on your system.\n");
		return -2;
	}
	wprintf(L"%d graphics adapters are available on your system.\n", g_enumAdapters.NumAdapters);
	
	for (size_t i = 0; i < g_enumAdapters.NumAdapters; i++)
	{
		D3DKMT_ADAPTERINFO adapterInfo = g_enumAdapters.Adapters[i];
		g_queryAdapterInfo.hAdapter = adapterInfo.hAdapter; 
		g_queryAdapterInfo.Type = KMTQAITYPE_DRIVER_DESCRIPTION;
		g_queryAdapterInfo.PrivateDriverDataSize = sizeof(D3DKMT_DRIVER_DESCRIPTION);
		g_queryAdapterInfo.pPrivateDriverData = &g_driverDescription;
		ntstatus = D3DKMTQueryAdapterInfo(&g_queryAdapterInfo);
		if (FAILED(ntstatus))
		{
			wprintf(L"Failed to query adapter description.\n");
			return -3;
		}
		wprintf(L"%d. %s\n", i + 1, g_driverDescription.DriverDescription);
	}
l_get_index:
	// Get the graphics adapter index for which to query the CASO support from the user.
	wprintf(L"Enter a graphics adapter index between (%d-%d): ", 1, g_enumAdapters.NumAdapters);
	wscanf_s(L"%d%*c", &g_graphicsAdapterIndex);
	// Normalize the index.
	--g_graphicsAdapterIndex;
	adapterHandle = g_enumAdapters.Adapters[g_graphicsAdapterIndex].hAdapter;

	D3DKMT_CROSSADAPTERRESOURCE_SUPPORT KernelSupport = { 0 };
	D3DKMT_QUERYADAPTERINFO QueryAdapterInfo;
	QueryAdapterInfo.hAdapter = adapterHandle;
	QueryAdapterInfo.Type = KMTQAITYPE_CROSSADAPTERRESOURCE_SUPPORT;
	QueryAdapterInfo.pPrivateDriverData = &KernelSupport;
	QueryAdapterInfo.PrivateDriverDataSize = sizeof(KernelSupport);
	if (FAILED(D3DKMTQueryAdapterInfo(&QueryAdapterInfo)))
	{
		wprintf(L"Failed to check CASO support.\n");
		return -4;
	}
	switch (KernelSupport.SupportTier)
	{ 
		case D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_NONE:
			wprintf(L"Your system doesn't support CASO. But this doesn't mean that it will never. Check the requirements section on the relevant blog to see that there is something to update.\n");
			break;
		case D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_COPY:
			wprintf(L"Your system support CASO tier 1." MORE_INFO_MESSAGE);
			break;
		case D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_TEXTURE:
			wprintf(L"Your system support CASO tier 2." MORE_INFO_MESSAGE);
			break;
		case D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_SCANOUT:
			wprintf(L"Your system support CASO tier 3 which means it has full support for CASO." MORE_INFO_MESSAGE);
			break; 
	}
	g_lookedUpIndices[g_graphicsAdapterIndex] = true;
	bool allLookedUp = true;
	for (size_t i = 0; i < g_enumAdapters.NumAdapters; i++)
	{
		if (!g_lookedUpIndices[i])
		{
			allLookedUp = false;
			break;
		}
	}
	if (allLookedUp)
		goto l_exit;
	wprintf(L"To query CASO for another adapter, type [y/Y] or [n/N] otherwise.\n");
	do 
	{ 
		wprintf(L"Do you want to query the CASO support for a different graphics adapter on your system?: ");
		wscanf_s(L"%c%*c", &answer);
		answer = tolower(answer);
		if (answer == L'y')
			goto l_get_index;
		else if (answer == L'n') 
			break; 
		else  
			wprintf(L"Type [y/Y] for \"yes\" or [n/N] for \"no\"\n"); 
	} while (answer != L'n' && answer != L'y');

	D3DKMT_CLOSEADAPTER ca;
	ca.hAdapter = adapterHandle;
l_exit:
	wprintf(L"Exiting...\n");
	ntstatus = D3DKMTCloseAdapter(&ca);
	return 0;
}