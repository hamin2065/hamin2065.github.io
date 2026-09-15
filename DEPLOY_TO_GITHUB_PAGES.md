# Deploy this site to hamin2065.github.io

Your `_config.yml` is already set for **https://hamin2065.github.io** (`url` and `baseurl: ""`).

## Steps

### 1. Add your GitHub Pages repo as a remote

From the project root (al-folio):

```bash
git remote add pages https://github.com/hamin2065/hamin2065.github.io.git
```

(Keep `origin` as the al-folio theme upstream so you can pull updates later.)

### 2. Push your site

- **If you want this site to replace everything in hamin2065.github.io** (recommended if that repo is an old/different site):

  ```bash
  git push pages main:master --force
  ```

  GitHub Pages for user sites uses the **master** or **main** branch; your repo may use `master`. This pushes your local `main` to `pages`’s `master` and overwrites the remote.

- **If your repo’s default branch is already `main`**:

  ```bash
  git push pages main
  ```

### 3. Enable GitHub Pages and GitHub Actions

1. On GitHub: **Settings → Pages**
   - Source: **GitHub Actions** (not “Deploy from a branch”).
2. The **Deploy site** workflow (`.github/workflows/deploy.yml`) will run on push and deploy the built `_site` to Pages.

### 4. Wait and open the site

After the workflow finishes (Actions tab), the site will be at **https://hamin2065.github.io**.

---

**Note:** If you use `--force`, the current contents of https://github.com/hamin2065/hamin2065.github.io will be replaced by this al-folio project. Back up anything you need from that repo first.
