workspace "OpenGL"

	architecture "x64"
	configurations {
		"Debug",
		"Release"
	}

outputDirName = "%{cfg.buildcfg}-%{cfg.architecture}"

project "OpenGL"
	location "src"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputDirName .. "/")
	objdir("obj/" .. outputDirName .. "/")

	files{
		"src/**.hpp",
		"src/**.cpp",
		"src/shaders/**.shader"
	}

	includedirs{
		"thirdparty/GLFW/include/",
		"thirdparty/GLEW/include/"
	}

	libdirs{
		"thirdparty/GLFW/lib/",
		"thirdparty/GLEW/lib/"

	}

	links {
		"glew32s", 
		"glfw3",
		"opengl32"
	}

	defines{
		"GLEW_STATIC"
	}