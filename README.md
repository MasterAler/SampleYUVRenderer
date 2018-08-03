# SampleYUVRenderer
Very basic sketch of rendering YUV frames via Qt/OpenGL

## What is it for?

**YUV** -- is a raw video file format. Sometimes you want to display it,
for example when displaying decoded video stream data. 


Here is a Proof-of-Concept sketch, demonstrating rendering of YUV frames (as follows from title).
There were times, when DirectX or Vdpau could beat OpenGL, the _old_ version of it, but rendering
a simple frame (okay, with YUV 2 RGB conversion) doesn't feel like something, which requires third party libraries.

## How it works?

Since Qt supports OpenGL ES with shaders and other fine stuff (starting with Qt 5.6 or so), you can obtain 
a well-behaving rendering widget, possible to be embedded in your widget app.

Cross-platform and _maybe_ even portable (depends on the drivers/hardware support etc).

### Where to get raw yuv file?

They are required for testing purposes. Google helpes.
[Here](http://trace.eas.asu.edu/yuv/), for example, you can get some.