WHITEBOARD
=========
> [!NOTE]
>  A **Whiteboard** is a temporary spot that notes are jotted down and then
> erased.  Use it for things like brainstorming, ideation, offloading, etc.
> These notes are ***not*** important and can be erased at any time.


 maybe what I've got as "features" in the readme should be more like a quickstart section and features should just outline what's included and briefly what they do

for a documentation style guide, look at how [take recorder](https://dev.epicgames.com/documentation/en-us/unreal-engine/record-gameplay-in-unreal-engine?application_version=5.5) is documented:

- menus are bolded and use '>' to indicate flow:  **File > Restart Editor....**
- steps in processes are numbered:
	1. do a thing
	2. do another thing
	3. then do the third thing
- paths in the content browser are also **Foldername > Foldername**
- any text that's quoted from the screen are bold, and mouse actions appear bolded
	- example: To remove a Component from the **Components** window, **Right-click** on the Component's name and select **Delete**.
- Icon's like settings are described this way: "select the Take Recorder **Settings** icon."
- explanatory notes pop out of the numbered sequence.
- The title of the article is an h1, topics are h2
- the toc is a dropdown after the title, a one line desc of the article, and a pretty header image
- They use a lot of overview tables when there's multiple settings or properties 
- lists of settings within a numbered list of steps (like what settings to set in a properties dialog before an export action), are just listed as bullets within the ordered list.
- callouts:
	- callouts are all one-liners - not multi paragraph
	- warnings:
> [!WARNING] It is important that the device and the computer are on the same physical network—check the WiFi settings on your iPhone to make sure.
- information (these are used pretty extensively):
> [!NOTE] Make sure you enable the Take Recorder plugin. You can do this by navigating to Edit > Plugins and searching for Take Recorder.
- Tips:
> [!TIP] If using the **Face AR Sample** app as a facial motion capture puppeteering device, it is recommended that you only show the Debug Mesh. This is faster, more performant, and has less of an impact on device thermals. This is important, as performance of the device diminishes if it overheats.
- when marking up screencaps, epic uses yellow boxes (sometimes numbered) and yellow arrows. Example:
5. **Left-click** the text in the Level Viewport to select it. Then in the **Details** panel, change its **Text** value to something else.
![](assets/media/Pasted%20image%2020241218170823.png)Press **Enter** to confirm the new text. Your changes will immediately appear in the Level Viewport.
    
2. From the **Main Toolbar**, click the **Possess** button (1), then click the **Resume** button (2).

- note in the example above, they numbered the buttons to indicate a sequence.
- they do refer, by name, to the **Main Toolbar** and **Main Menu**
- words like "button," "icon," "property," etc., are not bolded: ie. "Click the **Stop** button."
- They use a "card" metaphor when listing chapters or sections:
![](assets/media/Pasted%20image%2020241218171425.png)

