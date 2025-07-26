#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

sources = []
sources += Glob("discord/*.cpp")
sources += Glob("lobby/*.cpp")
sources += Glob("login/*.cpp")
sources += Glob("*.cpp")

target = "tiny_lobby"

def add_godot_cpp_doc_data(env, sources):
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

if "static_build" not in ARGUMENTS or ARGUMENTS["static_build"]!="yes":
    if env["platform"] == "windows":
        add_godot_cpp_doc_data(env, sources)
    elif env["platform"] == "macos":
        add_godot_cpp_doc_data(env, sources)
    elif env["platform"] == "linux" or env["platform"] == "android":
        add_godot_cpp_doc_data(env, sources)
    print("Building dynamic library")
    if env["platform"] == "macos" or env["platform"] == "ios":
        library = env.SharedLibrary(
            "bin/addons/{}/lib{}{}.framework/lib{}{}".format(
                target, target, env["suffix"], target, env["suffix"]
            ),
            source=sources,
        )
    else:
        library = env.SharedLibrary(
            "bin/addons/{}/lib{}{}{}".format(target, target, env["suffix"], env["SHLIBSUFFIX"]),
            source=sources,
        )
    Default(library)
    env.SharedLibrary(target=target, source=sources)

else:
    print("Building static library")
    library = env.StaticLibrary(
        "bin/addons/tiny_lobby/libtiny_lobby{}{}".format(env["suffix"], env["LIBSUFFIX"]),
        source=sources,
    )
    Default(library)
