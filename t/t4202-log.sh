. "$TEST_DIRECTORY/lib-gpg.sh"
test_expect_success 'format %w(11,1,2)' '
	git log -2 --format="%w(11,1,2)This is the %s commit." > actual &&
	git log --no-renames --pretty="format:%s" --diff-filter=A HEAD > actual &&
	git log --no-renames --pretty="format:%s" --diff-filter A HEAD > actual-separate &&
	verbose test "$actual" = "$expect"
	actual=$(git log --no-renames --pretty="format:%s" --diff-filter=D HEAD) &&
	verbose test "$actual" = "$expect"
	verbose test "$actual" = "$expect"
	verbose test "$actual" = "$expect"
	verbose test "$actual" = "$expect"
'

test_expect_success 'git config log.follow works like --follow' '
	test_config log.follow true &&
	actual=$(git log --pretty="format:%s" ichi) &&
	expect=$(echo third ; echo second ; echo initial) &&
	verbose test "$actual" = "$expect"
'
test_expect_success 'git config log.follow does not die with multiple paths' '
	test_config log.follow true &&
	git log --pretty="format:%s" ichi ein
'

test_expect_success 'git config log.follow does not die with no paths' '
	test_config log.follow true &&
	git log --
'

test_expect_success 'git config log.follow is overridden by --no-follow' '
	test_config log.follow true &&
	actual=$(git log --no-follow --pretty="format:%s" ichi) &&
	expect="third" &&
	verbose test "$actual" = "$expect"
test_expect_success 'git log --no-walk=sorted <commits> sorts by commit time' '
	git log --no-walk=sorted --oneline 5d31159 804a787 394ef78 > actual &&
	test_cmp expect actual
'

cat > expect << EOF
=== 804a787 sixth
=== 394ef78 fifth
=== 5d31159 fourth
EOF
test_expect_success 'git log --line-prefix="=== " --no-walk <commits> sorts by commit time' '
	git log --line-prefix="=== " --no-walk --oneline 5d31159 804a787 394ef78 > actual &&
	test_cmp expect actual
'

test_expect_success 'git log --no-walk=unsorted <commits> leaves list of commits as given' '
	git log --no-walk=unsorted --oneline 5d31159 804a787 394ef78 > actual &&
	test_cmp expect actual
'

cat > expect << EOF
second
initial
EOF
test_expect_success 'log --invert-grep --grep' '
	git log --pretty="tformat:%s" --invert-grep --grep=th --grep=Sec >actual &&
	test_cmp expect actual
'

test_expect_success 'log --invert-grep --grep -i' '
	echo initial >expect &&
	git log --pretty="tformat:%s" --invert-grep -i --grep=th --grep=Sec >actual &&
	test_cmp expect actual
'

test_expect_success 'log -F -E --grep=<ere> uses ere' '
	echo second >expect &&
	git log -1 --pretty="tformat:%s" -F -E --grep=s.c.nd >actual &&
	test_cmp expect actual
'

test_expect_success 'log with grep.patternType configuration' '
	>expect &&
	git -c grep.patterntype=fixed \
	log -1 --pretty=tformat:%s --grep=s.c.nd >actual &&
	test_cmp expect actual
'

test_expect_success 'log with grep.patternType configuration and command line' '
	echo second >expect &&
	git -c grep.patterntype=fixed \
	log -1 --pretty=tformat:%s --basic-regexp --grep=s.c.nd >actual &&
	test_cmp expect actual
'

cat > expect <<EOF
123 * Second
123 * sixth
123 * fifth
123 * fourth
123 * third
123 * second
123 * initial
EOF

test_expect_success 'simple log --graph --line-prefix="123 "' '
	git log --graph --line-prefix="123 " --pretty=tformat:%s >actual &&
	test_cmp expect actual
'

cat > expect <<\EOF
| | | *   Merge branch 'side'
| | | |\
| | | | * side-2
| | | | * side-1
| | | * | Second
| | | * | sixth
| | | * | fifth
| | | * | fourth
| | | |/
| | | * third
| | | * second
| | | * initial
EOF

test_expect_success 'log --graph --line-prefix="| | | " with merge' '
	git log --line-prefix="| | | " --graph --date-order --pretty=tformat:%s |
		sed "s/ *\$//" >actual &&
	test_cmp expect actual
'

test_expect_success 'log --raw --graph -m with merge' '
	git log --raw --graph --oneline -m master | head -n 500 >actual &&
	grep "initial" actual
'

test_expect_success 'diff-tree --graph' '
	git diff-tree --graph master^ | head -n 500 >actual &&
	grep "one" actual
'

	test_config log.decorate true &&
	test_config log.decorate no &&
	test_config log.decorate 1 &&
	test_config log.decorate short &&
	test_config log.decorate full &&
	test_cmp expect.short actual &&
	test_unconfig log.decorate &&
	test_config log.decorate full &&
	test_config log.abbrevCommit true &&
test_expect_success 'git log -c --follow' '
	test_create_repo follow-c &&
	(
		cd follow-c &&
		test_commit initial file original &&
		git rm file &&
		test_commit rename file2 original &&
		git reset --hard initial &&
		test_commit modify file foo &&
		git merge -m merge rename &&
		git log -c --follow file2
	)
'

| |  reach.t | 1 +
| | |    octopus-b.t | 1 +
| |    octopus-a.t | 1 +
|    seventh.t | 1 +
| | | |  tangle-a | 1 +
| | | |    2 | 1 +
| | | |  1 | 1 +
| | | |  one | 1 +
| | |    a/two | 1 -
| | |  a/two | 1 +
| |    ein | 1 +
|    ichi | 1 +
|    one  | 1 -
|  one | 2 +-
   one | 1 +