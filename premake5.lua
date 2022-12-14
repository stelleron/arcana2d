-- premake5.lua
workspace "Arcana2D"
    architecture "x64"
    configurations {"Debug", "Release"}

project "arcana2d"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/"

    files {"src/**.cpp"}
    includedirs {"external/include/", "src/"}
    libdirs {"external/lib/"}
    links {"glfw3", "glad", "GLUT.framework", "CoreVideo.framework", 
    "IOKit.framework", "OpenGL.framework", "Cocoa.framework"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/"

    files {"test/**.cpp"}
    includedirs {"external/include/", "src/"}
    libdirs {"build/"}
    links {"arcana2d"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"