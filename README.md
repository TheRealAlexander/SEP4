# SEP4

## Project Structure
This project is organized into a monorepo structure to facilitate development across Frontend, IoT, and Backend/Cloud components. Here's an overview of the directory structure:

- `/frontend` - Contains all the code related to the frontend application.
- `/iot` - Houses the IoT device code and related resources.
- `/backend` - Includes all backend and cloud-related code.

## How to Contribute
Contributions are welcomed following our structured branching strategy and pull request (PR) guidelines to maintain code quality and facilitate collaboration.

### Branching Strategy
We use a specific set of branches to manage the development and deployment process:
- `prod` - The production branch, represents the current state of the project in production.
- `dev` - The development branch, all feature and bugfix branches merge back into this branch. Essentially a staging area. The code should still pass tests and work here.
- `feature/*` - For new features, branch off from `dev`. Naming example: `feature/add-login`.
- `bugfix/*` - For bug fixes, also branch off from `dev`. Naming example: `bugfix/login-error`.

When working on a specific part of the project, prefix your branches accordingly, e.g., `frontend/feature/new-ui`, `iot/bugfix/connection-issue`.

### Pull Request Guide
1. **Create a Branch:** Based on our branching strategy, create your branch from `dev`. Use a clear name for your branch that reflects the contribution, following the pattern `component/type/description`, e.g., `frontend/feature/add-login`.
2. **Develop Your Feature or Fix:** Make your changes locally, ensuring they are well-documented and tested.
3. **Push Your Branch:** Once your changes are complete, push your branch to the repository.
4. **Open a Pull Request (PR):** Create a PR against the `dev` branch. Your PR should include a detailed description of the changes and any other relevant information for reviewers.
5. **Review Process:** At least two other team members must review and approve your PR before it can be merged. Ensure that any feedback is addressed promptly.
6. **Merge:** Once your PR has been approved and has passed all necessary checks, it can be merged into `dev`. `dev` will eventually be merged into `prod` incrementally as stable releases.

## Contribution Guidelines
- Ensure your code adheres to the project standards and guidelines.
- Write meaningful commit messages and provide a comprehensive description in your PRs.
- Run all tests and ensure they pass before submitting a PR.
- Participate in the review process for other contributions to share knowledge and maintain quality.
