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
