. "$TEST_DIRECTORY/lib-terminal.sh"
cat > expect.colors <<\EOF
*   Merge branch 'side'
<BLUE>|<RESET><CYAN>\<RESET>
<BLUE>|<RESET> * side-2
<BLUE>|<RESET> * side-1
* <CYAN>|<RESET> Second
* <CYAN>|<RESET> sixth
* <CYAN>|<RESET> fifth
* <CYAN>|<RESET> fourth
<CYAN>|<RESET><CYAN>/<RESET>
* third
* second
* initial
EOF

test_expect_success 'log --graph with merge with log.graphColors' '
	test_config log.graphColors " blue,invalid-color, cyan, red  , " &&
	git log --color=always --graph --date-order --pretty=tformat:%s |
		test_decode_color | sed "s/ *\$//" >actual &&
	test_cmp expect.colors actual
'

| * commit tags/side-2
	git log --oneline --no-decorate >expect.none &&
test_expect_success 'log.decorate config parsing' '
	git log --oneline --decorate=full >expect.full &&
	git log --oneline --decorate=short >expect.short &&

	test_config log.decorate full &&
	test_config log.mailmap true &&
	git log --oneline >actual &&
	test_cmp expect.full actual &&
	git log --oneline --decorate=short >actual &&
	test_cmp expect.short actual
'

test_expect_success TTY 'log output on a TTY' '
	git log --oneline --decorate >expect.short &&

	test_terminal git log --oneline >actual &&
	test_cmp expect.short actual
'

cat >expect <<-\EOF
* reach
|
| A	reach.t
* Merge branch 'tangle'
*   Merge branch 'side'
|\
| * side-2
|
|   A	2
* Second
|
| A	one
* sixth

  D	a/two
EOF

test_expect_success 'log --graph with --name-status' '
	git log --graph --format=%s --name-status tangle..reach >actual &&
	sanitize_output <actual >actual.sanitized &&
	test_cmp expect actual.sanitized
'

cat >expect <<-\EOF
* reach
|
| reach.t
* Merge branch 'tangle'
*   Merge branch 'side'
|\
| * side-2
|
|   2
* Second
|
| one
* sixth

  a/two
EOF

test_expect_success 'log --graph with --name-only' '
	git log --graph --format=%s --name-only tangle..reach >actual &&
	sanitize_output <actual >actual.sanitized &&
	test_cmp expect actual.sanitized
'

test_expect_success 'log --source paints symmetric ranges' '
	cat >expect <<-\EOF &&
	09e12a9	source-b three
	8e393e1	source-a two
	EOF
	git log --oneline --source source-a...source-b >actual &&
	test_cmp expect actual
'
