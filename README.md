## What is CASO?

Most laptops are designed by a hybrid architecture where it consists of two GPU for different tasks. An integrated GPU (iGPU) handles performance-unintensive tasks such as rendering desktop, web browsing, word editing programs etc. On the other hand, an external GPU (eGPU) exists for handling more power-intensive applications or tasks such as gaming, rendering 3D visual, CAD etc. When user starts a power-intensive application, system switches into external GPU automatically and to render and display a frame on the display device, first, frame rendered by eGPU must be duplicated and copied into system memory as a shared resource and iGPU also must copy this shared resource for itself. This copy process surely doesn't come for free, it costs some time, resulting in decrease in FPS.

To solve this architectural issue, GPU manufacturers introduced some solutions, including Nvidia's Nvidia Advanced Optimus and AMD's AMD Smart Access Graphics. However, not all laptops equipped with these technologies. So, Microsoft also introduced another solution named CASO. With CASO, there 
Cross Adapter Scan-Out

## CheckCASO

A minimal C program to check if your system supports **DirectX CASO ([Cross Adapter Scan-Out](https://devblogs.microsoft.com/directx/optimizing-hybrid-laptop-performance-with-cross-adapter-scan-out-caso/))** to boost your in-game FPS.
