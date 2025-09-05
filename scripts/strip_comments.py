import os
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
SRC_DIR = os.path.join(ROOT, 'src')

EXTS = {'.h', '.hpp', '.hh', '.cpp', '.cc', '.cxx'}


def strip_comments(code: str) -> str:
    out = []
    i = 0
    n = len(code)
    in_sl_comment = False
    in_ml_comment = False
    in_squote = False
    in_dquote = False
    while i < n:
        c = code[i]
        nxt = code[i+1] if i + 1 < n else ''

        if in_sl_comment:
            if c == '\n':
                in_sl_comment = False
                out.append(c)
            # else skip chars inside // comment
            i += 1
            continue

        if in_ml_comment:
            if c == '*' and nxt == '/':
                in_ml_comment = False
                i += 2
            else:
                i += 1
            continue

        if in_squote:
            out.append(c)
            if c == '\\':  # escape
                if i + 1 < n:
                    out.append(code[i+1])
                    i += 2
                    continue
            if c == "'":
                in_squote = False
            i += 1
            continue

        if in_dquote:
            out.append(c)
            if c == '\\':  # escape
                if i + 1 < n:
                    out.append(code[i+1])
                    i += 2
                    continue
            if c == '"':
                in_dquote = False
            i += 1
            continue

        # Not in any string/comment
        if c == '/' and nxt == '/':
            in_sl_comment = True
            i += 2
            continue
        if c == '/' and nxt == '*':
            in_ml_comment = True
            i += 2
            continue
        if c == '"':
            in_dquote = True
            out.append(c)
            i += 1
            continue
        if c == "'":
            in_squote = True
            out.append(c)
            i += 1
            continue

        out.append(c)
        i += 1

    return ''.join(out)


def should_process(path: str) -> bool:
    # Process only within src; skip build artifacts just in case
    if os.sep + 'release' + os.sep in path.lower():
        return False
    if os.sep + 'debug' + os.sep in path.lower():
        return False
    if os.sep + 'build' + os.sep in path.lower():
        return False
    _, ext = os.path.splitext(path)
    return ext.lower() in EXTS


def main():
    changed = 0
    files = []
    for root, dirs, filenames in os.walk(SRC_DIR):
        # Optional: skip moc_ generated files if any appear under src
        filenames = [f for f in filenames if not f.startswith('moc_')]
        for f in filenames:
            path = os.path.join(root, f)
            if should_process(path):
                files.append(path)

    for path in files:
        with open(path, 'r', encoding='utf-8', errors='ignore') as fh:
            original = fh.read()
        stripped = strip_comments(original)
        if stripped != original:
            with open(path, 'w', encoding='utf-8') as fh:
                fh.write(stripped)
            changed += 1
            print(f"Stripped comments: {os.path.relpath(path, ROOT)}")

    print(f"Done. Files changed: {changed}/{len(files)}")


if __name__ == '__main__':
    main()
