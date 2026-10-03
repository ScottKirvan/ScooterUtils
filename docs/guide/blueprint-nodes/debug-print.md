# Debug Print Node

Write timestamped debug messages to the Output Log and, optionally, to a log file.

**Category:** **Scooter Utilities** > **Debug Print**

## Log Message

Writes a message to the **Output Log** and, if you give it a file name, appends the same line, as UTF-8 text, to a log file in your project's `Saved/Logs` folder.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Log File** | Input | The log file to append to, relative to `Saved/Logs`. Example: `MyGame.log` or `Debug/Testing.log`. Leave empty to write only to the **Output Log**. |
| **Level** | Input | The severity label for the message: **Info**, **Warning**, **Error**, or **Critical**. |
| **Content** | Input | The message to log. |
| **Context** | Input (advanced) | Optional text that says where the message came from, like `PlayerController` or `SaveGame`. Expand the node's advanced pins to see it. |
| **Return Value** | Output | **true** if the message was logged. When **Log File** is set, **false** means the file couldn't be written. |

## Message Format

Each message is formatted as:

```
[<timestamp>] <Context>: <LEVEL>: <Content>
```

The timestamp uses a "stardate" style format: `YYYY.DDD.HHMMSS`, where `DDD` is the day of the year. When **Context** is empty, it's left out along with its colon.

Messages appear in the **Output Log** under the `LogDebugPrint` category.

> [!NOTE]
> **Level** is written into the message text. All messages appear in the **Output Log** at the normal log verbosity, so filter on the label (for example, `ERROR:`) rather than the **Output Log**'s Warnings or Errors filters.

## Example

1. Call **Log Message** with **Log File** set to `MyGame.log`, **Level** set to **Info**, **Content** set to `Player joined: ` + the player's name, and **Context** set to `Multiplayer`.

2. The message appears in the **Output Log** and is appended to `Saved/Logs/MyGame.log`:

   ```
   [2025.283.143052] Multiplayer: INFO: Player joined: Steve
   ```

> [!TIP]
> Writing from C++? The `SCOOTER_DEBUG_PRINT` macro adds the source file and line number as the context automatically.
