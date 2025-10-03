# Contributing: Embedded Architect Mode

Welcome to the Embedded Architect mode! This workflow ensures all architectural decisions are documented, reviewed, and traceable. Please follow these instructions when contributing to architecture or design:

## Architectural Documentation Workflow

1. **Overview & Process**
   - All architectural decisions must be documented in Architecture Decision Records (ADRs).
   - The architectural overview is maintained in `architecture.md`.
   - Each ADR must use the template in `docs/adr-template.md`.

2. **ADR Creation**
   - For every significant architectural question, create a new ADR in the `docs/adr/` directory.
   - Use the ADR template and fill out all sections.
   - Reference the ADR in `architecture.md`.

3. **Review & Approval**
   - Submit ADRs via pull request.
   - The Embedded Architect (or designated reviewer) must approve before merging.

4. **Updating Overview**
   - After an ADR is accepted, update `architecture.md` to summarize the decision and link to the ADR.

## References
- Architectural overview: `architecture.md`
- ADR template: `docs/adr-template.md`
- ADRs directory: `docs/adr/`


## Development Lifecycle & Contribution Rules

Development is performed incrementally. For each increment:
1. **Planning:**
   - Define all files and modules to be created or modified.
   - Specify method/function signatures and document implementation instructions as comments in code.
   - Plan documentation updates for any affected files (README, architecture.md, etc.).
2. **Implementation:**
   - Implement code for each method/function according to the documented instructions.
   - Use AI tools (e.g., Copilot) for boilerplate, refactoring, and documentation, but always review logic and security manually.
   - Note in comments or commit messages if code is AI-generated for traceability.
3. **Code Quality & Testing:**
   - Run code formatters (e.g., clang-format) and linters (e.g., cppcheck) before review.
   - Implement or update unit/integration tests for new/modified code.
   - Compile the code after each increment.
   - If compilation errors occur, analyze and identify the root cause.
   - Fix errors and recompile until the code builds successfully.
4. **Documentation Update:**
   - Update relevant documentation (README, architecture.md, module docs) as part of each increment.
5. **Review:**
   - Ensure code matches planned structure and instructions.
   - Submit changes via pull request for review and approval.
   - For minor changes or bug fixes, a streamlined process may be used (e.g., direct commit with clear documentation and code review).

**AI Usage Guidelines:**
- Use AI tools to accelerate development, but always verify correctness, security, and maintainability.
- Prompt AI with clear instructions and review all generated code before merging.
- Attribute AI-generated code in comments or commit messages.

This process ensures professional, maintainable, and error-free code development, with best practices for AI-driven workflows and automated code quality.


---

# ProductOwner Mode: Requirements Engineering Workflow

This workflow ensures all business requirements are clearly documented, reviewed, and traceable. Please follow these instructions when contributing user stories or updating the roadmap:

## User Story Creation
- Write user stories using the Connextra format:
   - `As a [user/role], I want [feature] so that [benefit].`
- Define acceptance criteria using Gherkin syntax:
   - `Given [context], When [action], Then [outcome].`
- Use the template in `.github/chatmodes/ProductOwner-Templates/USER_STORY_TEMPLATE.md`.
- Name user story files as `US-<number>-<short-title>.md` and store in `docs/stories/`.
- Number user stories sequentially and uniquely.
- Update the status field as the story progresses (Draft, Reviewed, Implemented).

## Roadmap Management
- The roadmap is maintained in `ROADMAP.md` at the project root.
- Add new user stories in priority order.
- Track status and milestones for each story.
- Link each entry to the corresponding user story markdown file in `docs/stories/`.
- Use the template in `.github/chatmodes/ProductOwner-Templates/ROADMAP_TEMPLATE.md` for structure and instructions.

## Review & Approval
- All user stories and roadmap changes must be reviewed and approved by the Product Owner.
- Submit changes via pull request for review.

## References
- ProductOwner chatmode: `.github/chatmodes/ProductOwner.chatmode.md`
- User story template: `.github/chatmodes/ProductOwner-Templates/USER_STORY_TEMPLATE.md`
- Roadmap template: `.github/chatmodes/ProductOwner-Templates/ROADMAP_TEMPLATE.md`

For questions, contact the Product Owner or project maintainer.
