
// System
#include <iostream>
#include <stdio.h>
#include <string>
#include <cinttypes>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <cassert>

// Third party
#include <window_wrapper.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>

// Project
#include "yellow_math.h"
#include "integers.h"
#include "opengl_wrapper.h"
#include "shader.h"
#include "program.h"
#include "rendering.h"
#include "scene.h"
#include "file.h"
#include "asset_manager.h"
#include "importing.h"
#include "timers.h"
#include "win32_platform.h"