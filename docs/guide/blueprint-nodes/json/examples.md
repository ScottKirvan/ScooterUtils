# JSON Examples and Troubleshooting

Real-world recipes for the JSON nodes, plus tips and fixes for common problems.

The examples on this page use a shorthand for Blueprint graphs: each `→` is the output of one node feeding into the next, and `-` marks the **JSON String** input that comes from the previous node.

## Examples

### Save Player Data

Build a save object, then write it to disk with the [File IO](../file-io) nodes.

```
SaveData = ""
  → Add Field(String, -, "playerName", PlayerName)
  → Add Field(Number, -, "level", LevelAsString)
  → Add Field(Number, -, "health", HealthAsString)
  → Add Field(Number, -, "maxHealth", MaxHealthAsString)
  → Add Array Field(String Array, -, "inventory", InventoryItems)

Save Text To File(Project Saved Directory, "SaveGames/save_slot_1.json", SaveData)
```

### Load Player Data

Read the file back, validate it, then pull out each value.

```
Load File To String(Project Saved Directory, "SaveGames/save_slot_1.json") → JSONString

if Is Valid JSON(JSONString):
    Get String Field(JSONString, "playerName") → PlayerName
    Get Number Field(JSONString, "level") → Level
    Get Number Field(JSONString, "health") → Health
    Get Array Field(String Array, JSONString, "inventory") → Inventory
```

### Build a Nested Structure

A character sheet with nested equipment objects.

```
// Build equipment
Weapon = ""
  → Add Field(String, -, "name", "Excalibur")
  → Add Field(Number, -, "damage", "50")
  → Add Field(String, -, "type", "Sword")

Armor = ""
  → Add Field(String, -, "name", "Plate Mail")
  → Add Field(Number, -, "defense", "30")

// Build character
Character = ""
  → Add Field(String, -, "name", "Sir Lancelot")
  → Add Field(Number, -, "level", "20")
  → Add Object Field(-, "weapon", Weapon)
  → Add Object Field(-, "armor", Armor)
```

The result, formatted for readability:

```json
{
  "name": "Sir Lancelot",
  "level": 20,
  "weapon": {
    "name": "Excalibur",
    "damage": 50,
    "type": "Sword"
  },
  "armor": {
    "name": "Plate Mail",
    "defense": 30
  }
}
```

### Work with Arrays of Objects

A leaderboard built from player objects, then read back in a loop.

```
// Create player entries
Player1 = ""
  → Add Field(String, -, "name", "Alice")
  → Add Field(Number, -, "score", "100")

Player2 = ""
  → Add Field(String, -, "name", "Bob")
  → Add Field(Number, -, "score", "150")

// Create leaderboard
Leaderboard = ""
  → Add Array Field(Object Array, -, "players", [Player1, Player2])

// Later: read it back
Get Array Field(Object Array, Leaderboard, "players") → PlayerStrings

For Each PlayerString in PlayerStrings:
    Get String Field(PlayerString, "name") → Name
    Get Number Field(PlayerString, "score") → Score
    Print String: Name + " scored " + Score
```

## Tips and Best Practices

* **Always validate external JSON.** If JSON comes from files, web APIs, or user input, check it with **Is Valid JSON** first.
* **Use Pretty Print for debugging.** When things aren't working, run your JSON through **Pretty Print JSON** and print it to the screen. You'll instantly see what your data looks like.
* **Start simple, then nest.** Build your JSON from the inside out: create the inner objects first, then nest them in the outer ones.
* **Remember that everything is strings.** When creating JSON, all values go in as strings and the nodes convert them based on type. When reading number arrays, values come back as strings.
* **Check that fields exist.** Use **Has Field** before the getter nodes when you're working with data that might be incomplete.
* **Chain your nodes.** The output of one creation node feeds right into the next. Start with an empty string, then chain the adds.
* **Use the File IO nodes to save and load.** The JSON nodes only work with strings. The [File IO](../file-io) nodes handle reading and writing them to disk.
* **Don't forget object arrays.** The **Object Array** type is perfect for lists of complex items, like inventory, enemies, or quests.

## Troubleshooting

### My JSON looks weird

* Run it through **Pretty Print JSON** and print it to see the structure.
* Make sure you're chaining each node's **JSON String Out** into the next node's **JSON String**.

### A getter node returns false

* Check that the field exists with **Has Field**.
* Validate the JSON with **Is Valid JSON**.
* Make sure the field name matches exactly. Field names are case-sensitive.
* **Get Array Field** and **Get Object Field** also return **false** if the field exists but isn't the expected type.

### My data disappeared after an add node

* If the **JSON String** input isn't a valid JSON object, the add nodes start over with an empty object. Check the input with **Is Valid JSON**.

### Numbers aren't working right

* When reading number arrays, values come back as strings like `"100.0"`.
* When creating, make sure you've picked the **Number** type, not **String**.
* Empty or non-numeric strings become `0`.

### My nested objects are broken

* Build inner objects completely before nesting them.
* Use **Get Object Field** to extract nested JSON, then parse the result again.

### My array is empty

* Check that you're using the right **Array Type** when reading. For example, an **Object Array** skips elements that aren't objects.
* Verify the array exists with **Has Field**.
* Make sure the JSON is valid.
