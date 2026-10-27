# Smart Food Court Seat Display System

A static web dashboard based on the original C++ Smart Food Court Seat Display System.

## Features
- Dashboard for 10 tables
- Best-fit table assignment for customer groups
- Release assigned tables
- Filter by vacant, partially occupied, and occupied
- Occupancy summary and usage percentage
- Saves state in the current browser with localStorage
- Responsive layout for desktop and mobile

## Run locally
Open `index.html` in a modern web browser.

## Deploy on GitHub Pages
1. Create a GitHub repository named `smart-food-court`.
2. Upload `index.html` and `README.md` to the repository root.
3. Commit the files to the `main` branch.
4. Open repository **Settings → Pages**.
5. Under **Build and deployment**, select **Deploy from a branch**.
6. Choose branch `main` and folder `/(root)`, then click **Save**.
7. Wait for the deployment to finish. Your URL will be:
   `https://YOUR-USERNAME.github.io/smart-food-court/`

Replace `YOUR-USERNAME` with your GitHub username.

## Important notes
- GitHub Pages hosts the browser version; it does not compile or execute the original C++ source.
- Table state is stored separately in each browser and is not synchronized across devices.
