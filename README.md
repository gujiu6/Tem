# gujiu6 XCPC LaTeX 模板

本项目以 [Kendieer/XCPC-Templates](https://github.com/Kendieer/XCPC-Templates) 的 LaTeX 文档结构、章节样式、封面与 minted 代码高亮为排版基础；算法代码全部来自 [gujiu6/Tem](https://github.com/gujiu6/Tem)，不保留原 LaTeX 仓库中的算法代码。

## 编译

安装 TeX Live（包含 XeLaTeX、ctex、minted）和 Python Pygments。在项目根目录执行两遍：

```bash
xelatex -shell-escape -interaction=nonstopmode -halt-on-error main.tex
xelatex -shell-escape -interaction=nonstopmode -halt-on-error main.tex
```

第二遍用于刷新目录和页码。编译时需允许 shell escape，以便 minted 调用 Pygments 生成代码高亮。

## 目录结构

- `main.tex`：中文书籍样式、封面、章节标题、目录、页眉页脚与配色。
- `vslight.style.minted`：原模板的 VS Code Light Modern 风格代码高亮。
- `frontmatter/preface.tex`：本项目的前言与编译说明。
- `chapters/`：按专题组织代码文件的 LaTeX 章节。
- `code/`：从 `gujiu6/Tem` 复制的原始 C++ 文件，内容不改写。

## 来源

- LaTeX 排版模板：[Kendieer/XCPC-Templates](https://github.com/Kendieer/XCPC-Templates)
- C++ 代码模板：[gujiu6/Tem](https://github.com/gujiu6/Tem)
