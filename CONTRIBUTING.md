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

## Additional Guidelines
- Keep documentation clear and concise.
- Discuss alternatives and rationale in ADRs.
- Use consistent terminology and structure.

For questions, contact the Embedded Architect or project maintainer.
