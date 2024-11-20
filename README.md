## Setting the Scene

Most gaming laptops today are designed with a hybrid architecture with two GPUs to meet different performance needs and increase battery life. An integrated GPU (also abbreviated to iGPU for short) handles tasks that don't require high computation resources, such as rendering the desktop, web browsing, word editing programs, etc. On the other hand, a discrete GPU (dGPU) exists for handling more power-intensive applications or tasks such as gaming, rendering 3D visuals, CAD, etc. In this architecture, the display device is usually connected to the iGPU. When a user starts a power-intensive application, the system switches into the external GPU automatically. The dGPU renders the frame and passes it over to the iGPU for the frame to be displayed onto the display device. Before passing it over to the iGPU, first, the frame rendered by eGPU must be duplicated and copied into the system memory as a shared resource. The iGPU then also must copy the frame from this shared resource to be able to display it. This double copy of the frame surely doesn't come for free; it costs some time, resulting in a noticeable decrease in FPS.

To solve this architectural issue, GPU manufacturers introduced some hardware-based solutions, including Nvidia's Nvidia Advanced Optimus and AMD's AMD Smart Access Graphics. However, not all laptops equipped with these hardware technologies. So, Microsoft also introduced a software-based solution named CASO. Unlike the hardware solutions using a multiplexer, with CASO (**Cross Adapter Scan-Out**), the need for two copies of the frames rendered by the discrete GPU is eliminated with an architectural optimization in Direct3D Kernel Subsystem. 

However, not all the hybrid laptops support the CASO and, Microsoft shares the system requirements as in the following table.

<img src="https://github.com/semihartan/CheckCASO/assets/13886510/1bc3ebdc-e342-4c96-ab34-0fc519cfbd90" width="50%" height="auto" alt="requirements"></img>

## CheckCASO

What is CheckCASO? and what does it do? CheckCASO is a minimal C program to check if your system supports **DirectX CASO ([Cross Adapter Scan-Out](https://devblogs.microsoft.com/directx/optimizing-hybrid-laptop-performance-with-cross-adapter-scan-out-caso/))**.
