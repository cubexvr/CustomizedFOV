# OpenXR API Layer for customizing the FOV of an VR headset

A lot of users cannot see (for various reasons, e.g. their individual headshape) the whole rendered FOV of their headset. 
So in order to gain performance it is useful to reduce the FOV to the part the user can actually see.
This is what this simple layer is all about. In addition to reducing the FOV by a factor the layer also scales the resolution accordingly, to keep the ppd the same. 
In order to do this correctly the layer has once to be active in a openXR session, i.e. you have once to start an random openXR application which actually renders something in VR. 
After that the FOV values of your headset will be known to the layer and appear in these registry values (values are in degrees multiplied by 1000):

  Computer\HKEY_CURRENT_USER\Software\CustomizedFOV\angle_down
  Computer\HKEY_CURRENT_USER\Software\CustomizedFOV\angle_up

How to set the FOV Customization factors:

  Currently only up and down angles can be changed.
  To do so you have to edit the following registry DWORD values to set the individual factors which are used for scaling the fov. 
  The numerical value is the fov scaling factor * 1000, e.g. if you want to reduce the vertial fov to 80% you have to set fov_down and fov_up to 800 (which is interpreted as 0.8).
  You can of course just e.g. change the upper angle and leave the lower angle as it is (having the default value of 1000)
  
  Computer\HKEY_CURRENT_USER\Software\CustomizedFOV\fov_down
  Computer\HKEY_CURRENT_USER\Software\CustomizedFOV\fov_up

Download and Install: see the "Releases" link (to the right)


For building the layer yourself from the source you need:

- Visual Studio 2019 or above;
- NuGet package manager (installed via Visual Studio Installer);
- Python 3 interpreter (installed via Visual Studio Installer or externally available in your PATH).


DISCLAIMER: This software is distributed as-is, without any warranties or conditions of any kind. Use at your own risks.
