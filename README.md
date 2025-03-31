# An attempt at getting an iOS App bundled up properly with an AUv3 (.appex) plugin Bundle


On iOS, its possible to bundle a CoreAudio AUv3 plugin, into an .app bundle, for distribution.  

This is done by packaging the plugin as an .appex bundle and including it into the .apps' resource bundle.

This repo contains an attempt at building a CMake-based JUCE/Tracktion project which has two major pieces:

	* A sample "App" which has the sole purpose of being an app, available in the App Store
	* A sample "Plugin", which has the sole purpose of being bundled into the app, as an ".appex" resource, and thus available to other CoreAudio plugin hosts, such as Cubasis and Logic, on iOS

# Status:

So far, things aren't quite working right.  The complexity of requiring Tracktion as well as JUCE, while also having multiple targets (App and Plugin) to bundle, is a bit befuddling.  However, stay tuned, I'll get this working sooner or later ..

