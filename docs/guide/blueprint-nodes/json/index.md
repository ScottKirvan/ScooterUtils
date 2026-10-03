# JSON Blueprint Nodes

Create, parse, and manipulate JSON data in Blueprints.

**Category:** **Scooter Utilities** > **JSON**

JSON (JavaScript Object Notation) is the closest thing there is to a universal language for storing and sending data. Think of it as a super-organized notebook where you can write down anything: numbers, text, lists, even nested structures. The JSON nodes give you simple Blueprint building blocks for working with it, with no C++ or complicated APIs required.

With the JSON nodes, you can:

* Save game data like player stats, inventory, and settings.
* Talk to web APIs.
* Store configuration files.
* Exchange data between systems.
* Create structured save files that humans can actually read.

## How the JSON Nodes Work

Every JSON node works on plain **String** values. There's no special JSON object type to manage:

* **Creation nodes** take a JSON string, add or change something, and return the updated JSON string. Chain them together, starting from an empty string, to build up an object.
* **Parsing nodes** take a JSON string and read something out of it.

All values go in as strings, too. The node converts each value based on the type you pick from its dropdown.

> [!NOTE]
> The JSON nodes work with JSON objects (`{...}`) at the top level. A string that's only an array or a single value isn't treated as valid JSON.

## Quick Start

Here's the simplest possible example, creating a JSON object with a player name:

1. Add an **Add Field** node to your graph.

2. Set its inputs:
   * **Field Type**: **String**
   * **JSON String**: leave empty
   * **Field Name**: `PlayerName`
   * **Value**: `SuperGamer123`

3. The **JSON String Out** pin returns:

   ```json
   {"PlayerName":"SuperGamer123"}
   ```

That's it. You just made JSON.

## JSON Node Pages

<div class="card-grid">
  <a class="card" href="./creation.html">
    <strong>Creation Nodes</strong>
    <span>Add, remove, merge, and format fields.</span>
  </a>
  <a class="card" href="./parsing.html">
    <strong>Parsing Nodes</strong>
    <span>Validate JSON and read values out of it.</span>
  </a>
  <a class="card" href="./examples.html">
    <strong>Examples and Troubleshooting</strong>
    <span>Real-world recipes, tips, and fixes for common problems.</span>
  </a>
</div>

## JSON Quick Reference

| Type | Example | Description |
| ---- | ------- | ----------- |
| String | `"hello"` | Text in double quotes. |
| Number | `42` or `3.14` | Whole numbers or decimals, no quotes. |
| Boolean | `true` or `false` | No quotes. |
| Null | `null` | An explicitly empty value. |
| Array | `[1,2,3]` | A list of values in square brackets. |
| Object | `{"key":"value"}` | Named fields in curly braces. |

A few rules to keep in mind:

* Field names must be in double quotes.
* String values must be in double quotes.
* Numbers and booleans are not in quotes.
* Commas separate items, but there's no comma after the last one.
