#include <CL/cl.h>
#include <iostream>
#include <vector>

void queryOpenCLDevices()
{
    cl_uint platformCount;
    cl_int status = clGetPlatformIDs(0, nullptr, &platformCount);

    if (status != CL_SUCCESS || platformCount == 0)
    {
        std::cerr << "Failed to find any OpenCL platforms.\n";
        return;
    }

    std::vector<cl_platform_id> platforms(platformCount);
    clGetPlatformIDs(platformCount, platforms.data(), nullptr);

    std::cout << "Found " << platformCount << " OpenCL platform(s):\n";

    for (cl_uint i = 0; i < platformCount; ++i)
    {
        char platformName[128];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platformName), platformName, nullptr);
        std::cout << "  Platform " << i << ": " << platformName << "\n";

        cl_uint deviceCount;
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceCount);

        if (deviceCount == 0)
        {
            std::cout << "    No devices found on this platform.\n";
            continue;
        }

        std::vector<cl_device_id> devices(deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices.data(), nullptr);

        for (cl_uint j = 0; j < deviceCount; ++j)
        {
            char deviceName[128];
            cl_device_type deviceType;
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(deviceName), deviceName, nullptr);
            clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(deviceType), &deviceType, nullptr);

            std::string typeStr;
            if (deviceType & CL_DEVICE_TYPE_CPU)
                typeStr += "CPU ";
            if (deviceType & CL_DEVICE_TYPE_GPU)
                typeStr += "GPU ";
            if (deviceType & CL_DEVICE_TYPE_ACCELERATOR)
                typeStr += "Accelerator ";
            if (deviceType & CL_DEVICE_TYPE_DEFAULT)
                typeStr += "Default ";

            std::cout << "    Device " << j << ": " << deviceName << " [" << typeStr << "]\n";
        }
    }
}
