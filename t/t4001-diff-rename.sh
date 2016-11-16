test_expect_success 'setup' '
	cat >path0 <<-\EOF &&
	Line 1
	Line 2
	Line 3
	Line 4
	Line 5
	Line 6
	Line 7
	Line 8
	Line 9
	Line 10
	line 11
	Line 12
	Line 13
	Line 14
	Line 15
	EOF
	cat >expected <<-\EOF &&
	diff --git a/path0 b/path1
	rename from path0
	rename to path1
	--- a/path0
	+++ b/path1
	@@ -8,7 +8,7 @@ Line 7
	 Line 8
	 Line 9
	 Line 10
	-line 11
	+Line 11
	 Line 12
	 Line 13
	 Line 14
	EOF
	cat >no-rename <<-\EOF
	diff --git a/path0 b/path0
	deleted file mode 100644
	index fdbec44..0000000
	--- a/path0
	+++ /dev/null
	@@ -1,15 +0,0 @@
	-Line 1
	-Line 2
	-Line 3
	-Line 4
	-Line 5
	-Line 6
	-Line 7
	-Line 8
	-Line 9
	-Line 10
	-line 11
	-Line 12
	-Line 13
	-Line 14
	-Line 15
	diff --git a/path1 b/path1
	new file mode 100644
	index 0000000..752c50e
	--- /dev/null
	+++ b/path1
	@@ -0,0 +1,15 @@
	+Line 1
	+Line 2
	+Line 3
	+Line 4
	+Line 5
	+Line 6
	+Line 7
	+Line 8
	+Line 9
	+Line 10
	+Line 11
	+Line 12
	+Line 13
	+Line 14
	+Line 15
	EOF

test_expect_success 'test diff.renames=true' '
	git -c diff.renames=true diff --cached $tree >current &&
	compare_diff_patch current expected
'

test_expect_success 'test diff.renames=false' '
	git -c diff.renames=false diff --cached $tree >current &&
	compare_diff_patch current no-rename
'

test_expect_success 'test diff.renames unset' '
	git diff --cached $tree >current &&
	compare_diff_patch current expected
'

test_expect_success 'two files with same basename and same content' '
	git reset --hard &&
	mkdir -p dir/A dir/B &&
	cp path1 dir/A/file &&
	cp path1 dir/B/file &&
	git add dir &&
	git commit -m 2 &&
	git mv dir other-dir &&
	git status | test_i18ngrep "renamed: .*dir/A/file -> other-dir/A/file"
'

test_expect_success 'rename pretty print with nothing in common' '
	mkdir -p a/b/ &&
	: >a/b/c &&
	git add a/b/c &&
	git commit -m "create a/b/c" &&
	mkdir -p c/b/ &&
	git mv a/b/c c/b/a &&
	git commit -m "a/b/c -> c/b/a" &&
	git diff -M --summary HEAD^ HEAD >output &&
	test_i18ngrep " a/b/c => c/b/a " output &&
	git diff -M --stat HEAD^ HEAD >output &&
	test_i18ngrep " a/b/c => c/b/a " output
'

test_expect_success 'rename pretty print with common prefix' '
	mkdir -p c/d &&
	git mv c/b/a c/d/e &&
	git commit -m "c/b/a -> c/d/e" &&
	git diff -M --summary HEAD^ HEAD >output &&
	test_i18ngrep " c/{b/a => d/e} " output &&
	git diff -M --stat HEAD^ HEAD >output &&
	test_i18ngrep " c/{b/a => d/e} " output
'

test_expect_success 'rename pretty print with common suffix' '
	mkdir d &&
	git mv c/d/e d/e &&
	git commit -m "c/d/e -> d/e" &&
	git diff -M --summary HEAD^ HEAD >output &&
	test_i18ngrep " {c/d => d}/e " output &&
	git diff -M --stat HEAD^ HEAD >output &&
	test_i18ngrep " {c/d => d}/e " output
'

test_expect_success 'rename pretty print with common prefix and suffix' '
	mkdir d/f &&
	git mv d/e d/f/e &&
	git commit -m "d/e -> d/f/e" &&
	git diff -M --summary HEAD^ HEAD >output &&
	test_i18ngrep " d/{ => f}/e " output &&
	git diff -M --stat HEAD^ HEAD >output &&
	test_i18ngrep " d/{ => f}/e " output
'

test_expect_success 'rename pretty print common prefix and suffix overlap' '
	mkdir d/f/f &&
	git mv d/f/e d/f/f/e &&
	git commit -m "d/f/e d/f/f/e" &&
	git diff -M --summary HEAD^ HEAD >output &&
	test_i18ngrep " d/f/{ => f}/e " output &&
	git diff -M --stat HEAD^ HEAD >output &&
	test_i18ngrep " d/f/{ => f}/e " output
'
