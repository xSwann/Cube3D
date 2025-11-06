## 🧭 Organisation Git

### 🔹 Branche principale  
**main** → contient toujours une version stable et fonctionnelle du projet.

### 🔹 Branches de développement  
Chaque nouvelle fonctionnalité se fait sur une **branche dédiée**, puis est mergée dans **main** une fois terminée et testée.

**Exemples :**
- swann/parser  
- name/raycasting  
- swann/textures  
- name/minimap  

---

## 🧠 Commandes Git utiles

### 🆕 Créer une nouvelle branche  
Avant de commencer une nouvelle fonctionnalité :

```bash
git checkout main             # se placer sur la branche principale
git pull origin main          # récupérer la dernière version
git checkout -b swann/parser
```

### 💾 Sauvegarder et envoyer son travail  
```bash
git add .
git commit -m "feat: start parser"
git push origin swann/parser
```

### 🔁 Mettre à jour sa branche avec main  
Avant de merge, pour éviter les conflits :

```bash
git checkout main
git pull origin main
git checkout feature/parser
git merge main
```

---

## 🚀 Fusionner dans main

Quand une feature est terminée :

1. Aller sur **GitHub**  
2. Créer une **Pull Request** → de `name/...` vers `main`  
3. Le binôme vérifie et valide ✅  
4. Merge sur GitHub  
5. Ensuite, chacun met à jour sa branche **main** localement :

```bash
git checkout main
git pull origin main
```

---

## 💬 Règles de commit

**Format recommandé :**
```
<type>: <message clair>
```

**Types courants :**
- feat: nouvelle fonctionnalité  
- fix: correction  
- refactor: réécriture interne  
- style: norminette / indentation  
- docs: README, commentaires  

**Exemples :**
```bash
git commit -m "feat: implement raycasting loop"
git commit -m "fix: leak in texture loading"
git commit -m "style: fix norminette warnings"
```

---

## 🧹 Bonnes pratiques

- Toujours **pull avant de coder** :
  ```bash
  git checkout main
  git pull origin main
  ```
- Ne jamais coder directement sur **main**  
- Une **branche = une fonctionnalité**  
- Commit fréquents et explicites  
- Toujours compiler sans warnings (`-Wall -Wextra -Werror`)  

---

## 🧩 Schéma du flux Git

```
(main)───┐
         ├───► feature/parser ──┐
         │                      ├───► merge → main
         ├───► feature/raycast ─┘
         │
         ▼
       (main stable)
```

---
