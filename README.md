## What is CASO?

Most laptops are designed by a hybrid architecture where it consists of two GPU for different tasks. An integrated GPU (iGPU) handles performance-unintensive tasks such as rendering desktop, web browsing, word editing programs etc. On the other hand, an external GPU (eGPU) exists for handling more power-intensive applications or tasks such as gaming, rendering 3D visual, CAD etc. When user starts a power-intensive application, system switches into external GPU automatically and to render and display a frame on the display device, first, frame rendered by eGPU must be duplicated and copied into system memory as a shared resource and iGPU also must copy this shared resource for itself. This copy process surely doesn't come for free, it costs some time, resulting in decrease in FPS.

To solve this architectural issue, GPU manufacturers introduced some solutions, including Nvidia's Nvidia Advanced Optimus and AMD's AMD Smart Access Graphics. However, not all laptops equipped with these technologies. So, Microsoft also introduced another solution named CASO. Unlike the hardware solutions using a multiplexer, with CASO (**Cross Adapter Scan-Out**), which is a software solution, the need for two copies of the frames rendered by the discrete GPU is eliminated with an architectural optimization in Direct3D Kernel Subsystem. 

However, not all the hybrid laptops support the CASO and, Microsoft shares the system requirements as in the following table.

![image](https://github.com/semihartan/CheckCASO/assets/13886510/1bc3ebdc-e342-4c96-ab34-0fc519cfbd90)

### CheckCASO

What is CheckCASO? and what does it do? CheckCASO is  a minimal C program to check if your system supports **DirectX CASO ([Cross Adapter Scan-Out](https://devblogs.microsoft.com/directx/optimizing-hybrid-laptop-performance-with-cross-adapter-scan-out-caso/))** to boost your in-game FPS.
