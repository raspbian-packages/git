test_expect_success 'format %w(12,1,2)' '
	git log -2 --format="%w(12,1,2)This is the %s commit." > actual &&
	git log --pretty="format:%s" --diff-filter=A HEAD > actual &&
	git log --pretty="format:%s" --diff-filter A HEAD > actual-separate &&
	test "$actual" = "$expect" || {
		echo Oops
		echo "Actual: $actual"
		false
	}
	actual=$(git log --pretty="format:%s" --diff-filter=D HEAD) &&
	test "$actual" = "$expect" || {
		echo Oops
		echo "Actual: $actual"
		false
	}
	test "$actual" = "$expect" || {
		echo Oops
		echo "Actual: $actual"
		false
	}
	test "$actual" = "$expect" || {
		echo Oops
		echo "Actual: $actual"
		false
	}
	test "$actual" = "$expect" || {
		echo Oops
		echo "Actual: $actual"
		false
	}
| * commit side
	test_might_fail git config --unset-all log.decorate &&

	git log --oneline >expect.none &&
	git config --unset-all log.decorate &&
	git config log.decorate true &&
	git config --unset-all log.decorate &&
	git config log.decorate no &&
	git config --unset-all log.decorate &&
	git config log.decorate 1 &&
	git config --unset-all log.decorate &&
	git config log.decorate short &&
	git config --unset-all log.decorate &&
	git config log.decorate full &&
	test_cmp expect.short actual
	git config --unset-all log.decorate &&
	git config log.decorate full &&
	test_might_fail git config --remove-section log &&
	test_when_finished "git config --unset log.abbrevCommit" &&

	test_might_fail git config --unset log.abbrevCommit &&

	git config log.abbrevCommit true &&
| |  reach.t |    1 +
| | |    octopus-b.t |    1 +
| |    octopus-a.t |    1 +
|    seventh.t |    1 +
| | | |  tangle-a |    1 +
| | | |    2 |    1 +
| | | |  1 |    1 +
| | | |  one |    1 +
| | |    a/two |    1 -
| | |  a/two |    1 +
| |    ein |    1 +
|    ichi |    1 +
|    one  |    1 -
|  one |    2 +-
   one |    1 +