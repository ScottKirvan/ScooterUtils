# Lorem Ipsum Nodes

Generate placeholder text for UI mockups, art passes, and layout testing.

**Category:** **Scooter Utilities** > **Lorem Ipsum**

Quickly fill text blocks with realistic-looking dummy text, with no copying and pasting real content. It's perfect for designers and UI artists who need to see how a layout holds up with different amounts of text.

## Node Reference

| Node | Inputs | Output | Description |
| ---- | ------ | ------ | ----------- |
| **Generate Lorem Ipsum** | Num Paragraphs (default **3**), Min Sentences Per Paragraph (default **4**), Max Sentences Per Paragraph (default **8**) | String | Generates paragraphs of text. Each paragraph has a random number of sentences between the minimum and maximum. Paragraphs are separated by a blank line. |
| **Generate Sentences** | Num Sentences | String | Generates the given number of sentences, separated by spaces. |
| **Generate Words** | Num Words | String | Generates the given number of lowercase words, separated by spaces, with no punctuation. Good for button labels and short descriptions. |

Each sentence is 8 to 16 random words long, starts with a capital letter, ends with a period, and has the occasional comma. The text is randomized on every call.

## Example

Call **Generate Lorem Ipsum** with **Num Paragraphs** set to **2** and plug the result into a **Text Block**'s **Set Text** node to see how your UI handles a couple of paragraphs.
