#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/normal.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include <cstdlib>
#include <cstdint>
#include <cstddef> // for offsetof
#include <cmath>
#include <exception>
#include <type_traits>
#include <memory>
#include <iterator>
#include <functional>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <chrono>
#include <thread>
#include <random>

/* Project Libs */

#include "JustUtility.h"

#endif // !STDAFX_H
