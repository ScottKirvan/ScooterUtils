# CLAUDE.md — ScooterUtils

ScooterUtils is an Unreal Engine plugin (UE 5.5–5.8 on `main`; older engines live on the
`All-Versions-Prior-to-5.1`, `UE-5.1-to-5.2`, and `UE-5.3-to-5.4` branches). It has an
editor-only module (`Source/ScooterUtils`: menus, toolbar, persistent Editor Preferences)
and a runtime Blueprint library module (`Source/ScooterUtilsBPLibrary`: JSON, File IO,
Global Config, Debug Print, Blueprint Reflection, Lorem Ipsum).

## Documentation

- User documentation lives in the VitePress site under `docs/` (`docs/guide/`), deployed
  by `.github/workflows/docs.yml` to https://www.scottkirvan.com/ScooterUtils/.
- Build locally: `cd docs && npm ci && npx vitepress build` (the build fails on dead links).
- Pages follow Unreal Engine 5.8 documentation conventions: H1 title plus one-line summary,
  each menu segment bolded (**Edit** > **Plugins**), numbered procedures, Name/Description
  tables, one-line `> [!NOTE]`/`[!TIP]`/`[!WARNING]` callouts. Keep the tone light, no emoji.
- Document behavior from the source, not from header comments — several comments are stale.
- Design specs for larger changes live in `notes/dev/specs/` (e.g. `json-node-redesign.md`).

## Keeping This File Current

This file is the primary context for any agent working in this repo — keep it accurate
as the project evolves. When you learn what the project is, add a brief description at
the top. As key files, build commands, and architectural decisions emerge, record them
here so future sessions start with full context rather than re-deriving it.

Update this file in the same commit as the work it documents.

## Working Conventions

- Never commit or push directly to `main`. Always branch first, then PR.
- Before pushing to, or building new commits on, a previously-used branch, run `git
  fetch --prune` and confirm its remote ref still exists — a merged PR's branch may
  already be gone. At the start of any session resuming an existing branch, `git fetch
  origin && git rebase origin/main` before touching files — branches drift silently
  between sessions.
- Branch names must describe the work (e.g. `fix/login-timeout`, `feat/export-csv`).
  No random characters, UUIDs, or generated suffixes to ensure uniqueness — if a name
  is already taken, pick a more specific descriptive name instead.
- If a branch name is pre-assigned by tooling (a hosted agent session, a CI runner)
  rather than chosen by you, verify it against this convention before the first push.
  Rename locally (`git branch -m <name>`) if it doesn't match — being handed a name
  isn't an exemption from the rule.
- One concern per branch and PR. If work naturally splits into independent problems,
  split the branches too — resist bundling unrelated changes into one PR.
- Conventional commits: `feat:` / `fix:` / `docs:` / `chore:` / `refactor:` / `test:`.
  Breaking: `feat!:`.
- `feat:` is for genuinely new user-facing capabilities only. Bug fixes and corrections
  use `fix:`, even when they close a tracked issue.
- Unit tests must be written alongside all new code. All bug fixes require red/green
  tests — a failing test that reproduces the bug, then the fix that makes it pass.
- CI, lint, and formatting must all pass before committing or opening a PR. Discover
  the project's commands from the CI config, `package.json`, `Makefile`, or equivalent
  — do not assume they match another project's toolchain.
- Prefer narrow, localised changes. Favour modularity that contains the blast radius
  of future edits — a fix or feature should not require touching unrelated parts of
  the codebase. If it does, that's a design signal worth surfacing.
- Refactoring is a first-class activity, not something to defer. Improve structure as
  you go rather than accumulating technical debt for a later pass.
- When working in unfamiliar domain territory, prefer primary sources — official docs,
  specs, RFCs — over general knowledge. Flag domain uncertainty explicitly rather than
  proceeding on an assumption.
- Default to writing no comments. Add one only when the *why* is non-obvious — a
  hidden constraint, a subtle invariant, a workaround for a specific bug. If code is
  hard to understand, the fix is clearer naming and structure, not a comment explaining
  what it does.

## Change as Experiment

Work proceeds in small, verifiable, safe, directed steps — not a plan executed end to
end. Each step is small enough to evaluate on its own: land it, check whether it moved
things in the right direction, then decide the next step from what was just learned
rather than from what was originally guessed. Treat every change as an experiment with
a check at the end, not a commitment to a predetermined path.

This project runs in a constrained environment on purpose — the impulse to run ahead,
anticipate the next three steps, or solve adjacent problems while already in the code
is explicitly suppressed. Staying inside the current step is a discipline, not a
limitation to work around.

## Testing Strategy

Tests are the fastest mechanical check that generated code matches intent — treat them
as load-bearing, not optional scaffolding. Two tiers matter most here:

- **Unit tests**, written alongside the code (see Working Conventions above) — TDD
  where practical: the test exists before the implementation it verifies.
- **Acceptance tests**, written in behavior terms (given/when/then or equivalent) —
  describing what the system does from the outside, not how. These are the actual spec
  for a feature or fix; if a change can't be stated as an acceptance criterion, the
  requirement isn't clear enough yet to build against.

When a process mistake gets logged in `notes/dev/mistakes.md`, ask whether it's also a
missing test — a regression or acceptance test that would have caught it mechanically
next time, not just a process note relying on memory.

## No Shortcuts

Nothing is deferred without explicit permission from the user. A known issue is still
a bug — do not mark it "won't fix", "by design", or "out of scope" unilaterally.

If a library or package cannot meet the stated requirements, the answer is to find an
alternative or do the work from first principles — not to defer the requirement or
revise it to fit the limitation. The requirements define what the project needs; the
implementation serves the requirements, not the other way around.

## Verification Discipline

Never state that something works, is fixed, or is verified unless it was checked at
that exact moment with a command whose output is the actual basis for the claim — not
memory of an earlier check, not knowledge of what the code is supposed to do, and not
a sub-agent's self-report taken at face value. The standard is identical in both
directions: the skepticism applied to a sub-agent's "done" (see Sub-Agent Workflow)
applies just as much to Claude's own claims to the user.

Before reporting a task or verification as complete:
- State the concrete, checkable success criteria before running anything — specific
  facts ("a PR exists against branch X containing files A and B"), not a general
  expectation ("it should work").
- Check every criterion with a fresh command at the time of the claim, and cite its
  actual output as the basis for what's reported.
- If a task has multiple required scenarios (e.g. two code paths, or a dev environment
  and the real deployment target), track them explicitly and don't report the whole
  task done until every one has been checked — a passing sub-step is not a finished
  task.
- Report against the criteria list: state plainly what's verified and what isn't,
  rather than describing the completed part in success language and leaving gaps
  implicit.

## Communication

Ask questions in natural language. Never use a multiple choice / structured question
tool — including Claude Code's `AskUserQuestion` tool — if clarification is needed,
just ask directly in plain text. This is a project-wide preference, not a
per-session one: some interfaces render binned/multiple-choice questions poorly,
and forcing a question into fixed options loses the nuance an open question
would surface. Standard engineering practice is to ask a real question and read
a real answer, not to pick from a menu.

## Autonomy

Make implementation decisions independently — don't ask permission for technical
choices within the stated requirements. Escalate only when something would change
scope, defer a requirement, or contradict what the user has described as the goal.

A structural choice made while implementing a functional request — naming, module
boundaries, a relationship between two pieces — is mine to propose, but must be
flagged as a proposal, not written into this file, a spec, or code comments with the
same authority as something the user actually decided.

A description of a desired change is not, by itself, authorization to execute it. If a
message separates *what* to do from *when* ("I'll tell you when"), wait for the
explicit go-ahead before acting — even on a fully-specified, low-risk change.

**IF YOU CANNOT DO EXACTLY WHAT WAS ASKED — DUE TO A TECHNICAL CONSTRAINT OR ANY OTHER
REASON — STATE THE CONSTRAINT AND STOP.** Do not silently substitute an alternative and
proceed to implement it in the same turn. Naming the blocker is not itself permission
to pick a workaround; the user decides which alternative (if any) to pursue. This
applies even when the substitute seems obviously reasonable.

**Two-strike auto-comply.** If corrected twice on the same point, treat the second
correction as an automatic stop: comply immediately, with no further justification or
re-explanation. Don't make the user repeat themselves a third time or invoke a
stop-word to get compliance — repetition itself is the signal.

**Mark proposals as proposals.** Any architectural or structural choice made while
implementing — one not a direct restatement of something the user actually decided —
gets written into a spec, `CLAUDE.md`, or other persistent doc as `[Proposed —
unconfirmed]`, not plain declarative text carrying the same authority as a real
decision. Don't unmark your own proposal; only the user confirming it (or leaving it
alone) makes it settled.

## Attribution

No attribution of any kind in commit messages, PR bodies, or issue text — no
"Generated with", "Co-Authored-By", "Created by Claude", or any AI/tool credit lines.

**Verify by reading the repo, not from memory.** Some git hosting integrations inject
a footer server-side even into a request that omitted one — treat that as expected
behavior, not a surprise. After every commit and after every PR create/update, re-read
the actual result and strip any attribution found, regardless of source:
- Run `git log` and read the actual commit messages
- Re-fetch and read the actual PR body text
- Remove any attribution found, regardless of source

A commit or PR is not finished until this read-back check has run — don't rely on what
you wrote, check what actually landed.

## GitHub Issues and PRs

Issue and PR templates live in `ScottKirvan/.github` (or your org's equivalent) and
apply to this repo automatically via GitHub's community health file fallback.

- Bug reports → `[BUG]` title prefix, `bug_report.md` sections
- Feature requests → `[FEATURE]` title prefix, `feature_request.md` sections
- General → `[GENERAL]` title prefix, `general_report.md` sections
- PRs → fill all checklist sections; no attribution anywhere in the body

Before creating any issue: check for duplicates first — `gh issue list --state open
--limit 100` where the `gh` CLI is available, or the equivalent GitHub search/list
tool (e.g. an MCP GitHub server's `search_issues`/`list_issues`) in hosted sessions
that don't have `gh`. Don't skip the check just because the literal command doesn't
apply in a given environment.
Create issues only when explicitly asked — don't preemptively file future work.

## Sub-Agent Workflow

When using sub-agents for implementation:

- Brief sub-agents on **what** to build, not **how** — implementation decisions belong
  to the sub-agent, which serves as an independent second opinion on the approach.
- Not every implementation choice is "how." A choice is **load-bearing** — and belongs
  in the brief as a stated constraint, not left implicit — if getting it wrong would
  foreclose a decision already made elsewhere, or if fixing it later would cascade into
  sibling components rather than staying local to the one being built. The test: would
  changing this later touch only this component, or would it touch others or
  contradict something already decided? Local and reversible → genuinely "how,"
  delegate freely. Cascading or hard to reverse → state it explicitly in the brief.
  (Architecture — how two components relate, e.g. whether one delegates to the other —
  is the case that's easiest to misclassify as "how" when it's actually load-bearing.)
- Sub-agents follow all conventions in this file except they do not create PRs.
- After a sub-agent completes, review its diff and tests before creating the PR.
  This review is a genuine code review, not a compliance check — evaluate correctness,
  requirement alignment, and test quality independently.
- Simple issues found in review may be fixed directly. Significant deviations from the
  stated requirements or complex problems go back to the sub-agent rather than being
  patched over.
- Create the PR only after review passes.
