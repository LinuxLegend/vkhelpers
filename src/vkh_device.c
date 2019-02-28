/*
 * Copyright (c) 2018 Jean-Philippe Bruyère <jp_bruyere@hotmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "vkh_device.h"

VkhDevice vkh_device_create (VkPhysicalDevice phy, VkDevice vkDev) {
    VkhDevice dev = (vkh_device_t*)malloc(sizeof(vkh_device_t));
    dev->dev = vkDev;
    dev->phy = phy;

    vkGetPhysicalDeviceMemoryProperties (phy, &dev->phyMemProps);

    VmaAllocatorCreateInfo allocatorInfo = {
        .physicalDevice = phy,
        .device = vkDev
    };
    vmaCreateAllocator(&allocatorInfo, &dev->allocator);

    return dev;
}

void vkh_device_destroy (VkhDevice dev) {
    vmaDestroyAllocator (dev->allocator);
    vkDestroyDevice (dev->dev, NULL);
    free (dev);
}
