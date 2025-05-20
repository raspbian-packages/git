#!/bin/sh

test_description='check broken or malicious patterns in .git* files

Such as:

  - presence of .. in submodule names;
    Exercise the name-checking function on a variety of names, and then give a
    real-world setup that confirms we catch this in practice.

  - nested submodule names

  - symlinked .gitmodules, etc
'

TEST_PASSES_SANITIZE_LEAK=true
. ./test-lib.sh
. "$TEST_DIRECTORY"/lib-pack.sh

test_expect_success SYMLINKS,!WINDOWS,!MINGW 'submodule must not checkout into different directory' '
	test_when_finished "rm -rf sub repo bad-clone" &&

	git init sub &&
	write_script sub/post-checkout <<-\EOF &&
	touch "$PWD/foo"
	EOF
	git -C sub add post-checkout &&
	git -C sub commit -m hook &&

	git init repo &&
	git -C repo -c protocol.file.allow=always submodule add "$PWD/sub" sub &&
	git -C repo mv sub $(printf "sub\r") &&

	# Ensure config values containing CR are wrapped in quotes.
	git config --unset -f repo/.gitmodules submodule.sub.path &&
	printf "\tpath = \"sub\r\"\n" >>repo/.gitmodules &&

	git config --unset -f repo/.git/modules/sub/config core.worktree &&
	{
		printf "[core]\n" &&
		printf "\tworktree = \"../../../sub\r\"\n"
	} >>repo/.git/modules/sub/config &&

	ln -s .git/modules/sub/hooks repo/sub &&
	git -C repo add -A &&
	git -C repo commit -m submodule &&

	git -c protocol.file.allow=always clone --recurse-submodules repo bad-clone &&
	! test -f "$PWD/foo" &&
	test -f $(printf "bad-clone/sub\r/post-checkout")
'

test_done
