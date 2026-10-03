# Scooter Utilities Blueprint Nodes

An overview of the Blueprint nodes included with Scooter Utilities.

Scooter Utilities includes a runtime Blueprint library with practical helpers grouped by purpose. Unlike the editor tools, these nodes work in packaged games as well as in the editor. You can also call them from your own code; see the [C++ Reference](../cpp/).

## Node Categories

All nodes live under the **Scooter Utilities** category in the Blueprint node browser.

| Category | Description |
| -------- | ----------- |
| [JSON](./json/) | Build, parse, and modify JSON strings. |
| [File IO](./file-io) | Load, save, and append text files in the project's `Saved` or `Content` folders, or the user's Documents folder. |
| [Global Config](./global-config) | Read and write values in the engine's config (`Engine.ini`). |
| [Debug Print](./debug-print) | Write timestamped messages to the **Output Log** and, optionally, a log file. |
| [Blueprint Reflection](./blueprint-reflection) | Find out which Blueprint a call came from, along with its content paths. |
| [Lorem Ipsum](./lorem-ipsum) | Generate placeholder text for UI mockups and layout testing. |

## Finding Nodes

1. Open any Blueprint and **Right-click** on the graph to open the node browser.

2. Type **Scooter Utilities** to list every node, or search with keywords like **json**, **config**, **log**, **file**, or **lorem**.

Each node has a tooltip that describes its parameters and behavior. Hover over a node or one of its pins to see it.

## Editor-Only Behavior and Packaging

Some nodes, like [Get Calling Blueprint Path](./blueprint-reflection#get-calling-blueprint-path) and [Get Calling Blueprint Info](./blueprint-reflection#get-calling-blueprint-info), return the most detailed information in editor builds. In packaged builds they fall back to class-level information. See each node's page for details.

> [!TIP]
> Need an example? If you'd like code snippets or Blueprint graphs for any of these nodes, [open an issue](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D) and ask.
