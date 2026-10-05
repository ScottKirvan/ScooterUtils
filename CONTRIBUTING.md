# Contributing to ScooterUtils

First off, thank you for considering contributing to ScooterUtils! It's people like you that make this plugin better for everyone.

## How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check the existing issues to avoid duplicates. When you create a bug report, include as many details as possible using our bug report template.

**Guidelines for bug reports:**
- Use a clear and descriptive title
- Describe the exact steps to reproduce the problem
- Provide specific examples to demonstrate the steps
- Describe the behavior you observed and what you expected to see
- Include screenshots or Output Log excerpts if applicable
- Note your environment (OS, Unreal Engine version, plugin version)

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, use our feature request template and include:

- A clear and descriptive title
- A detailed description of the proposed feature
- Examples of how the feature would be used
- Why this enhancement would be useful

### Pull Requests

**Before submitting a pull request:**

1. Fork the repository and create your branch from `main`
2. If you've added code, add tests if applicable
3. Ensure your code follows the existing style
4. Make sure your commits follow the commit message conventions below
5. Update documentation as needed — user-facing changes belong in the [User Guide](docs/guide/)

## Commit Message Conventions

This project uses [Conventional Commits](https://www.conventionalcommits.org/) with [Semantic Versioning](https://semver.org/). Release-Please reads your commit messages to determine the next version number and generate the CHANGELOG automatically — so the type prefix matters.

| Prefix | Effect | Use for |
|--------|--------|---------|
| `feat:` | Bumps **MINOR** version | New features |
| `fix:` | Bumps **PATCH** version | Bug fixes and corrections |
| `docs:` | No version bump | Documentation only |
| `chore:` | No version bump | Maintenance, generated files |
| `refactor:` | No version bump | Code restructuring |
| `test:` | No version bump | Adding or updating tests |
| `feat!:` / `fix!:` / `xxx!:` | Bumps **MAJOR** version | Breaking changes |

**Examples:**
```
feat: add persistent viewport realtime toggle
fix: restore application scale after editor restart
docs: update installation instructions
feat!: rename Blueprint node categories
```

> **Tip:** When in doubt between `feat:` and `fix:`, use `fix:` — it's the right call for corrections to existing behavior even when they close a tracked issue.

## Pull Request Process

1. Update the [User Guide](docs/guide/) if your change affects user-facing behavior, and README.md if it affects building or the repo itself
2. CHANGELOG.md is updated automatically by Release-Please — do not edit it manually
3. The PR will be merged once approved by a maintainer
4. Your PR should pass all CI checks and have no merge conflicts

## Development Setup

1. Fork and clone the repository into the `Plugins` folder of an Unreal Engine C++ project (UE 5.5–5.8 for `main`)
2. Create a new branch for your feature or fix: `git checkout -b feat/your-feature origin/main`
3. Make your changes and build the project from your IDE (or let the editor build the plugin on launch)
4. Test your changes in the editor, and in a packaged build for changes to the runtime Blueprint library
5. Submit a pull request

### Building from the command line

You can build and package the plugin without opening the editor, using the engine's `RunUAT` (Windows paths shown):

```
"<UE_PATH>\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="<path>\ScooterUtils.uplugin" -Package="D:\sub\out" -TargetPlatforms=Win64 -Rocket
```

- Keep the `-Package` path short. Intermediate file paths are deep, and a long output folder pushes them past Windows' 260-character limit, so the build fails with `OtherCompilationError`.
- `BuildPlugin` rewrites the packaged `.uplugin`: it adds `EngineVersion`, converts legacy keys, and removes `EnabledByDefault`. That's expected for Fab packages.

To build the host project's editor target, which also compiles the plugin in place:

```
"<UE_PATH>\Engine\Build\BatchFiles\Build.bat" <Project>Editor Win64 Development -Project="<path>\<Project>.uproject" -WaitMutex
```

To run console commands in a headless editor, for example to exercise test code:

```
"<UE_PATH>\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "<path>\<Project>.uproject" -ExecCmds="<YourCommand>, QUIT_EDITOR" -unattended -nullrhi -nosplash -nosound -NoLiveCoding -abslog="<path>\run.log"
```

End `-ExecCmds` with `QUIT_EDITOR`. Plain `quit` doesn't close the full editor, so the process keeps running.

To work on the documentation site:

```
cd docs
npm ci
npx vitepress dev     # live preview
npx vitepress build   # production build; fails on dead links
```

## Project Structure

```
ScooterUtils/
├── .github/
│   ├── release-please/         # Release-Please config and version manifest
│   └── workflows/              # GitHub Actions workflows
├── Config/                     # Plugin packaging filters
├── Resources/                  # Plugin icon
├── Source/
│   ├── ScooterUtils/           # Editor-only module: menus, toolbar, Editor Preferences
│   └── ScooterUtilsBPLibrary/  # Runtime module: Blueprint node library
├── assets/
│   └── media/                  # Images and logos
├── docs/                       # VitePress documentation site
│   ├── .vitepress/             # VitePress config and theme
│   └── index.md                # Docs home page
├── notes/                      # CHANGELOG, VERSION, TODO, WHITEBOARD; dev/specs/ for design specs
├── tools/                      # Packaging scripts
├── CLAUDE.md                   # AI agent context (optional)
├── CONTRIBUTING.md             # This file
├── LICENSE.md
├── README.md
└── ScooterUtils.uplugin        # Plugin descriptor
```

> **Note:** Issue templates, PR templates, and funding config live in the org-level [`ScottKirvan/.github`](https://github.com/ScottKirvan/.github) repo and apply here automatically via GitHub's community health file fallback.

## Testing Plugin Changes

When making changes to the plugin, test by:

1. Building the plugin in a C++ project for each engine version you've touched (at minimum, the latest supported version)
2. Restarting the editor and confirming there are no new warnings or errors from `LogScooterUtils` or `LogDebugPrint` in the Output Log
3. Exercising the menus, toolbar, Editor Preferences, or Blueprint nodes you changed
4. For runtime Blueprint library changes, packaging a small test project and confirming the nodes behave the same outside the editor

## Questions?

Feel free to open an issue or reach out via:
- [LinkedIn](https://www.linkedin.com/in/scottkirvan/)
- [Discord](https://discord.gg/TN6XJSNK5Y)

Thank you for your contributions!
