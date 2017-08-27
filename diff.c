#include "sigchain.h"
int diff_use_color_default = -1;
	GIT_COLOR_NORMAL,	/* PLAIN */
static int parse_diff_color_slot(const char *var, int ofs)
	if (!strcasecmp(var+ofs, "plain"))
		return DIFF_PLAIN;
	if (!strcasecmp(var+ofs, "meta"))
	if (!strcasecmp(var+ofs, "frag"))
	if (!strcasecmp(var+ofs, "old"))
	if (!strcasecmp(var+ofs, "new"))
	if (!strcasecmp(var+ofs, "commit"))
	if (!strcasecmp(var+ofs, "whitespace"))
	if (!strcasecmp(var+ofs, "func"))
static int parse_dirstat_params(struct diff_options *options, const char *params,
	const char *p = params;
	int p_len, ret = 0;
	while (*p) {
		p_len = strchrnul(p, ',') - p;
		if (!memcmp(p, "changes", p_len)) {
		} else if (!memcmp(p, "lines", p_len)) {
		} else if (!memcmp(p, "files", p_len)) {
		} else if (!memcmp(p, "noncumulative", p_len)) {
		} else if (!memcmp(p, "cumulative", p_len)) {
			if (end - p == p_len)
				strbuf_addf(errmsg, _("  Failed to parse dirstat cut-off percentage '%.*s'\n"),
					    p_len, p);
			strbuf_addf(errmsg, _("  Unknown dirstat parameter '%.*s'\n"),
				    p_len, p);
		p += p_len;

		if (*p)
			p++; /* more parameters, swallow separator */
	if (!prefixcmp(var, "diff.color.") || !prefixcmp(var, "color.diff.")) {
		int slot = parse_diff_color_slot(var, 11);
		color_parse(value, var, diff_colors[slot]);
		return 0;
	if (!prefixcmp(var, "submodule."))
	const char *name; /* filename external diff should read from */
	char hex[41];
	char tmp_path[PATH_MAX];
	int *found_changesp;
	diff_populate_filespec(one, 1);
	if (o->output_prefix) {
		struct strbuf *msg = NULL;
		msg = o->output_prefix(o, o->output_prefix_data);
		assert(msg);
		fwrite(msg->buf, msg->len, 1, file);
	}
static void emit_add_line(const char *reset,
			  struct emit_callback *ecbdata,
			  const char *line, int len)
	const char *ws = diff_get_color(ecbdata->color_diff, DIFF_WHITESPACE);
	const char *set = diff_get_color(ecbdata->color_diff, DIFF_FILE_NEW);
	if (!*ws)
		emit_line_0(ecbdata->opt, set, reset, '+', line, len);
	else if (new_blank_line_at_eof(ecbdata, line, len))
		emit_line_0(ecbdata->opt, ws, reset, '+', line, len);
		emit_line_0(ecbdata->opt, set, reset, '+', "", 0);
	const char *plain = diff_get_color(ecbdata->color_diff, DIFF_PLAIN);
		emit_line(ecbdata->opt, plain, reset, line, len);
	strbuf_add(&msgbuf, frag, strlen(frag));
	strbuf_add(&msgbuf, reset, strlen(reset));
		strbuf_add(&msgbuf, plain, strlen(plain));
		strbuf_add(&msgbuf, reset, strlen(reset));
		strbuf_add(&msgbuf, func, strlen(func));
		strbuf_add(&msgbuf, reset, strlen(reset));
static int remove_tempfile_installed;

		if (diff_temp[i].name == diff_temp[i].tmp_path)
			unlink_or_warn(diff_temp[i].name);
static void remove_tempfile_on_signal(int signo)
{
	remove_tempfile();
	sigchain_pop(signo);
	raise(signo);
}

	const char *old = diff_get_color(ecb->color_diff, DIFF_FILE_OLD);
			emit_line_0(ecb->opt, old, reset, '-',
				    data, len);
		const char *plain = diff_get_color(ecb->color_diff,
						   DIFF_PLAIN);
		emit_line_0(ecb->opt, plain, reset, '\\',
	char *line_prefix = "";
	struct strbuf *msgbuf;

	if (o && o->output_prefix) {
		msgbuf = o->output_prefix(o, o->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
	ecbdata.found_changesp = &o->found_changes;
	ecbdata.ws_rule = whitespace_rule(name_b ? name_b : name_a);
 *   1. collect a the minus/plus lines of a diff hunk, divided into
	struct strbuf *msgbuf;
	char *line_prefix = "";
	if (opt->output_prefix) {
		msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
		if (!regexec(word_regex, buffer->ptr + *begin, 1, match, 0)) {
	struct strbuf *msgbuf;
	char *line_prefix = "";
	if (opt->output_prefix) {
		msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
	xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
		      &xpp, &xecfg);
		st->ctx.color = diff_get_color_opt(o, DIFF_PLAIN);
		free(ecbdata->diff_words);
		ecbdata->diff_words = NULL;
	const char *plain = diff_get_color(ecbdata->color_diff, DIFF_PLAIN);
	char *line_prefix = "";
	struct strbuf *msgbuf;
	if (o && o->output_prefix) {
		msgbuf = o->output_prefix(o, o->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
		fprintf(ecbdata->opt->file, "%s", ecbdata->header->buf);
	*(ecbdata->found_changesp) = 1;
		fprintf(ecbdata->opt->file, "%s%s--- %s%s%s\n",
		fprintf(ecbdata->opt->file, "%s%s+++ %s%s%s\n",
			putc('\n', ecbdata->opt->file);
		return;
	}

	if (len < 1) {
		emit_line(ecbdata->opt, reset, reset, line, len);
		if (ecbdata->diff_words
		    && ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN)
			fputs("~\n", ecbdata->opt->file);
		} else if (!prefixcmp(line, "\\ ")) {
			emit_line(ecbdata->opt, plain, reset, line, len);
			fputs("~\n", ecbdata->opt->file);
			emit_line(ecbdata->opt, plain, reset, line, len);
	if (line[0] != '+') {
		const char *color =
			diff_get_color(ecbdata->color_diff,
				       line[0] == '-' ? DIFF_FILE_OLD : DIFF_PLAIN);
		if (line[0] == ' ')
			ecbdata->lno_in_postimage++;
		emit_line(ecbdata->opt, color, reset, line, len);
	} else {
		emit_add_line(reset, ecbdata, line + 1, len - 1);
	while (a <= old && b <= new && *old == *new) {
	x = xcalloc(sizeof (*x), 1);
	if (diffstat->nr == diffstat->alloc) {
		diffstat->alloc = alloc_nr(diffstat->alloc);
		diffstat->files = xrealloc(diffstat->files,
				diffstat->alloc * sizeof(x));
	}
		return fputs(_(" 0 files changed\n"), fp);
		    Q_(" %d file changed", " %d files changed", files),
		/*
		 * TRANSLATORS: "+" in (+) is a line addition marker;
		 * do not translate it.
		 */
			    Q_(", %d insertion(+)", ", %d insertions(+)",
			       insertions),
		/*
		 * TRANSLATORS: "-" in (-) is a line removal marker;
		 * do not translate it.
		 */
			    Q_(", %d deletion(-)", ", %d deletions(-)",
			       deletions),
	int total_files = data->nr;
	int width, name_width, graph_width, number_width = 4, count;
	struct strbuf *msg = NULL;
	if (options->output_prefix) {
		msg = options->output_prefix(options, options->output_prefix_data);
		line_prefix = msg->buf;
	}

		if (!data->files[i]->is_renamed &&
			 (change == 0)) {
		if (file->is_binary || file->is_unmerged)
	count = i; /* min(count, data->nr) */
		width = term_columns() - options->output_prefix_length;
	graph_width = (options->stat_graph_width &&
		       options->stat_graph_width < max_change) ?
		options->stat_graph_width : max_change;
		char *name = data->files[i]->print_name;
		uintmax_t added = data->files[i]->added;
		uintmax_t deleted = data->files[i]->deleted;
		if (!data->files[i]->is_renamed &&
			 (added + deleted == 0)) {
			total_files--;
		}
		if (data->files[i]->is_binary) {
			fprintf(options->file, "  Bin ");
			fprintf(options->file, "%s%"PRIuMAX"%s",
		else if (data->files[i]->is_unmerged) {
			fprintf(options->file, "  Unmerged\n");
		adds += add;
		dels += del;
			int total = add + del;

			total = scale_linear(add + del, graph_width, max_change);
		fprintf(options->file, "%5"PRIuMAX"%s", added + deleted,
				added + deleted ? " " : "");
	for (i = count; i < data->nr; i++) {
		uintmax_t added = data->files[i]->added;
		uintmax_t deleted = data->files[i]->deleted;
		if (!data->files[i]->is_renamed &&
			 (added + deleted == 0)) {
		adds += added;
		dels += deleted;
		if (!data->files[i]->is_binary &&
		    !data->files[i]->is_unmerged) {
			int added = data->files[i]->added;
			int deleted= data->files[i]->deleted;
			if (!data->files[i]->is_renamed &&
			    (added + deleted == 0)) {
				total_files--;
			} else {
				adds += added;
				dels += deleted;
			}
	if (options->output_prefix) {
		struct strbuf *msg = NULL;
		msg = options->output_prefix(options,
				options->output_prefix_data);
		fprintf(options->file, "%s", msg->buf);
	}
		if (options->output_prefix) {
			struct strbuf *msg = NULL;
			msg = options->output_prefix(options,
					options->output_prefix_data);
			fprintf(options->file, "%s", msg->buf);
		}
	const char *line_prefix = "";
	struct strbuf *msg = NULL;

	if (opt->output_prefix) {
		msg = opt->output_prefix(opt, opt->output_prefix_data);
		line_prefix = msg->buf;
	}
		if (p->one->sha1_valid && p->two->sha1_valid)
			content_changed = hashcmp(p->one->sha1, p->two->sha1);
			diffcore_count_changes(p->one, p->two, NULL, NULL, 0,
			diff_populate_filespec(p->one, 1);
			diff_populate_filespec(p->two, 1);
	qsort(dir.files, dir.nr, sizeof(dir.files[0]), dirstat_compare);
			damage = (damage + 63) / 64;
	qsort(dir.files, dir.nr, sizeof(dir.files[0]), dirstat_compare);
	char *line_prefix = "";
	struct strbuf *msgbuf;
	if (data->o->output_prefix) {
		msgbuf = data->o->output_prefix(data->o,
			data->o->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
	memset(&stream, 0, sizeof(stream));
static void emit_binary_diff_body(FILE *file, mmfile_t *one, mmfile_t *two, char *prefix)
static void emit_binary_diff(FILE *file, mmfile_t *one, mmfile_t *two, char *prefix)
				diff_populate_filespec(one, 0);
			if (one->data)
	const char *set = diff_get_color_opt(o, DIFF_METAINFO);
	struct strbuf *msgbuf;
	char *line_prefix = "";
	if (o->output_prefix) {
		msgbuf = o->output_prefix(o, o->output_prefix_data);
		line_prefix = msgbuf->buf;
	if (DIFF_OPT_TST(o, SUBMODULE_LOG) &&
			(!one->mode || S_ISGITLINK(one->mode)) &&
			(!two->mode || S_ISGITLINK(two->mode))) {
		show_submodule_summary(o->file, one ? one->path : two->path,
				one->sha1, two->sha1, two->dirty_submodule,
				del, add, reset);
	diff_set_mnemonic_prefix(o, "a/", "b/");
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}

	strbuf_addf(&header, "%s%sdiff --git %s %s%s\n", line_prefix, set, a_one, b_two, reset);
		strbuf_addf(&header, "%s%snew file mode %06o%s\n", line_prefix, set, two->mode, reset);
		strbuf_addf(&header, "%s%sdeleted file mode %06o%s\n", line_prefix, set, one->mode, reset);
			strbuf_addf(&header, "%s%sold mode %06o%s\n", line_prefix, set, one->mode, reset);
			strbuf_addf(&header, "%s%snew mode %06o%s\n", line_prefix, set, two->mode, reset);
		ecbdata.found_changesp = &o->found_changes;
		ecbdata.ws_rule = whitespace_rule(name_b ? name_b : name_a);
		else if (!prefixcmp(diffopts, "--unified="))
			xecfg.ctxlen = strtoul(diffopts + 10, NULL, 10);
		else if (!prefixcmp(diffopts, "-u"))
			xecfg.ctxlen = strtoul(diffopts + 2, NULL, 10);
		xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
			      &xpp, &xecfg);
			     int complete_rewrite)
		data->added = diff_filespec_size(two);
		data->deleted = diff_filespec_size(one);
	else {
		xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
			      &xpp, &xecfg);
		xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
			      &xpp, &xecfg);
	int namelen = strlen(path);
	struct diff_filespec *spec = xmalloc(sizeof(*spec) + namelen + 1);
	memset(spec, 0, sizeof(*spec));
	spec->path = (char *)(spec + 1);
	memcpy(spec->path, path, namelen+1);
void fill_filespec(struct diff_filespec *spec, const unsigned char *sha1,
		   unsigned short mode)
		hashcpy(spec->sha1, sha1);
		spec->sha1_valid = !is_null_sha1(sha1);
static int reuse_worktree_file(const char *name, const unsigned char *sha1, int want_file)
	struct cache_entry *ce;
	if (!FAST_WORKING_DIRECTORY && !want_file && has_sha1_pack(sha1))
	if (hashcmp(sha1, ce->sha1) || !S_ISREG(ce->ce_mode))
static int populate_from_stdin(struct diff_filespec *s)
	size_t size = 0;

	if (strbuf_read(&buf, 0, 0) < 0)
		return error("error while reading from stdin %s",
				     strerror(errno));

	s->should_munmap = 0;
	s->data = strbuf_detach(&buf, &size);
	s->size = size;
	s->should_free = 1;
	return 0;
}

static int diff_populate_gitlink(struct diff_filespec *s, int size_only)
{
	int len;
	char *data = xmalloc(100), *dirty = "";
	len = snprintf(data, 100,
		       "Subproject commit %s%s\n", sha1_to_hex(s->sha1), dirty);
	s->data = data;
	s->size = len;
	s->should_free = 1;
		free(data);
int diff_populate_filespec(struct diff_filespec *s, int size_only)
	if (!s->sha1_valid ||
	    reuse_worktree_file(s->path, s->sha1, 0)) {
		if (!strcmp(s->path, "-"))
			return populate_from_stdin(s);

		if (size_only)
		if (convert_to_git(s->path, s->data, s->size, &buf, safe_crlf)) {
		if (size_only) {
			type = sha1_object_info(s->sha1, &s->size);
				die("unable to read %s", sha1_to_hex(s->sha1));
		} else {
			s->data = read_sha1_file(s->sha1, &type, &s->size);
			if (!s->data)
				die("unable to read %s", sha1_to_hex(s->sha1));
			s->should_free = 1;
	free(s->cnt_data);
	s->cnt_data = NULL;
			   const unsigned char *sha1,
	fd = git_mkstemps(temp->tmp_path, PATH_MAX, template.buf,
			strlen(base) + 1);
	close(fd);
	temp->name = temp->tmp_path;
	strcpy(temp->hex, sha1_to_hex(sha1));
	temp->hex[40] = 0;
	sprintf(temp->mode, "%06o", mode);
		strcpy(temp->hex, ".");
		strcpy(temp->mode, ".");
	if (!remove_tempfile_installed) {
		atexit(remove_tempfile);
		sigchain_push_common(remove_tempfile_on_signal);
		remove_tempfile_installed = 1;
	}

	if (!one->sha1_valid ||
	    reuse_worktree_file(name, one->sha1, 1)) {
				       (one->sha1_valid ?
					one->sha1 : null_sha1),
				       (one->sha1_valid ?
			if (!one->sha1_valid)
				strcpy(temp->hex, sha1_to_hex(null_sha1));
				strcpy(temp->hex, sha1_to_hex(one->sha1));
			 * !(one->sha1_valid), as long as
			sprintf(temp->mode, "%06o", one->mode);
			       one->sha1, one->mode);
			      int complete_rewrite)
	const char *spawn_arg[10];
	int retval;
	const char **arg = &spawn_arg[0];
		struct diff_tempfile *temp_one, *temp_two;
		const char *othername = (other ? other : name);
		temp_one = prepare_temp_file(name, one);
		temp_two = prepare_temp_file(othername, two);
		*arg++ = pgm;
		*arg++ = name;
		*arg++ = temp_one->name;
		*arg++ = temp_one->hex;
		*arg++ = temp_one->mode;
		*arg++ = temp_two->name;
		*arg++ = temp_two->hex;
		*arg++ = temp_two->mode;
		if (other) {
			*arg++ = other;
			*arg++ = xfrm_msg;
	} else {
		*arg++ = pgm;
		*arg++ = name;
	*arg = NULL;
	fflush(NULL);
	retval = run_command_v_opt(spawn_arg, RUN_USING_SHELL);
	if (retval) {
		fprintf(stderr, "external diff died, stopping at %s.\n", name);
		exit(1);
	}
	struct strbuf *msgbuf;
	char *line_prefix = "";
	if (o->output_prefix) {
		msgbuf = o->output_prefix(o, o->output_prefix_data);
		line_prefix = msgbuf->buf;
	}
	if (one && two && hashcmp(one->sha1, two->sha1)) {
		strbuf_addf(msg, "%s%sindex %s..", line_prefix, set,
			    find_unique_abbrev(one->sha1, abbrev));
		strbuf_addstr(msg, find_unique_abbrev(two->sha1, abbrev));
	if (!DIFF_OPT_TST(o, ALLOW_EXTERNAL))
		pgm = NULL;
	else {
				  complete_rewrite);
static void diff_fill_sha1_info(struct diff_filespec *one)
		if (!one->sha1_valid) {
			if (!strcmp(one->path, "-")) {
				hashcpy(one->sha1, null_sha1);
			if (index_path(one->sha1, one->path, &st, 0))
		hashclr(one->sha1);
	diff_fill_sha1_info(one);
	diff_fill_sha1_info(two);
	int complete_rewrite = 0;
		builtin_diffstat(p->one->path, NULL, NULL, NULL, diffstat, o, 0);
	diff_fill_sha1_info(p->one);
	diff_fill_sha1_info(p->two);
	if (p->status == DIFF_STATUS_MODIFIED && p->score)
		complete_rewrite = 1;
	builtin_diffstat(name, other, p->one, p->two, diffstat, o, complete_rewrite);
	diff_fill_sha1_info(p->one);
	diff_fill_sha1_info(p->two);
	options->context = 3;
int diff_setup_done(struct diff_options *options)
		die("--name-only, --name-status, --check and -s are mutually exclusive");
	if (options->abbrev <= 0 || 40 < options->abbrev)
	return 0;
	eq = strchr(arg, '=');
	if (eq)
		len = eq - arg;
	else
		len = strlen(arg);
	if (eq) {
	if (arg[0] != '-' || arg[1] != '-')
	arg += strlen("--");
	if (prefixcmp(arg, opt))
	arg += strlen(opt);
	if (*arg == '=') { /* sticked form: --option=value */
	arg += strlen("--stat");
		if (!prefixcmp(arg, "-width")) {
			arg += strlen("-width");
				die("Option '--stat-width' requires a value");
		} else if (!prefixcmp(arg, "-name-width")) {
			arg += strlen("-name-width");
				die("Option '--stat-name-width' requires a value");
		} else if (!prefixcmp(arg, "-graph-width")) {
			arg += strlen("-graph-width");
				die("Option '--stat-graph-width' requires a value");
		} else if (!prefixcmp(arg, "-count")) {
			arg += strlen("-count");
				die("Option '--stat-count' requires a value");
int diff_opt_parse(struct diff_options *options, const char **av, int ac)
	if (!strcmp(arg, "-p") || !strcmp(arg, "-u") || !strcmp(arg, "--patch"))
		options->output_format |= DIFF_FORMAT_PATCH;
	else if (opt_arg(arg, 'U', "unified", &options->context))
		options->output_format |= DIFF_FORMAT_PATCH;
	else if (!strcmp(arg, "--patch-with-raw"))
		options->output_format |= DIFF_FORMAT_PATCH | DIFF_FORMAT_RAW;
	else if (!strcmp(arg, "--numstat"))
	else if (!prefixcmp(arg, "-X"))
		return parse_dirstat_opt(options, arg + 2);
	else if (!prefixcmp(arg, "--dirstat="))
		return parse_dirstat_opt(options, arg + 10);
	else if (!prefixcmp(arg, "--dirstat-by-file=")) {
		return parse_dirstat_opt(options, arg + 18);
	else if (!strcmp(arg, "--patch-with-stat"))
		options->output_format |= DIFF_FORMAT_PATCH | DIFF_FORMAT_DIFFSTAT;
	else if (!strcmp(arg, "--name-only"))
	else if (!strcmp(arg, "-s"))
	else if (!prefixcmp(arg, "--stat"))
	else if (!prefixcmp(arg, "-B") || !prefixcmp(arg, "--break-rewrites=") ||
	else if (!prefixcmp(arg, "-M") || !prefixcmp(arg, "--find-renames=") ||
	else if (!prefixcmp(arg, "-C") || !prefixcmp(arg, "--find-copies=") ||
	else if (!prefixcmp(arg, "--relative=")) {
		options->prefix = arg + 11;
		options->output_format |= DIFF_FORMAT_PATCH;
	else if (!strcmp(arg, "--color"))
	else if (!prefixcmp(arg, "--color=")) {
		int value = git_config_colorbool(NULL, arg+8);
	else if (!prefixcmp(arg, "--color-words=")) {
		options->word_regex = arg + 14;
	else if (!prefixcmp(arg, "--word-diff=")) {
		const char *type = arg + 12;
		if (!strcmp(type, "plain"))
		else if (!strcmp(type, "color")) {
		else if (!strcmp(type, "porcelain"))
		else if (!strcmp(type, "none"))
			die("bad --word-diff argument: %s", type);
	} else if (!prefixcmp(arg, "--ignore-submodules=")) {
		handle_ignore_submodules_arg(options, arg + 20);
		DIFF_OPT_SET(options, SUBMODULE_LOG);
	else if (!prefixcmp(arg, "--submodule=")) {
		if (!strcmp(arg + 12, "log"))
			DIFF_OPT_SET(options, SUBMODULE_LOG);
	}
		options->orderfile = optarg;
		options->filter = optarg;
	else if (!prefixcmp(arg, "--abbrev=")) {
		options->abbrev = strtoul(arg + 9, NULL, 10);
		options->file = fopen(optarg, "w");
		if (!options->file)
			die_errno("Could not open '%s'", optarg);
		if (!prefixcmp(opt, "break-rewrites")) {
			opt += strlen("break-rewrites");
		} else if (!prefixcmp(opt, "find-copies")) {
			opt += strlen("find-copies");
		} else if (!prefixcmp(opt, "find-renames")) {
			opt += strlen("find-renames");
		return -1; /* that is not a -M, -C nor -B option */
	if (queue->alloc <= queue->nr) {
		queue->alloc = alloc_nr(queue->alloc);
		queue->queue = xrealloc(queue->queue,
					sizeof(dp) * queue->alloc);
	}
/* This is different from find_unique_abbrev() in that
 * it stuffs the result with dots for alignment.
 */
const char *diff_unique_abbrev(const unsigned char *sha1, int len)
	if (len == 40)
		return sha1_to_hex(sha1);
	abbrev = find_unique_abbrev(sha1, len);
	if (abblen < 37) {
		static char hex[41];
			sprintf(hex, "%s%.*s", abbrev, len+3-abblen, "..");
			sprintf(hex, "%s...", abbrev);
	return sha1_to_hex(sha1);
	if (opt->output_prefix) {
		struct strbuf *msg = NULL;
		msg = opt->output_prefix(opt, opt->output_prefix_data);
		fprintf(opt->file, "%s", msg->buf);
	}
			diff_unique_abbrev(p->one->sha1, opt->abbrev));
		fprintf(opt->file, "%s ", diff_unique_abbrev(p->two->sha1, opt->abbrev));
	if (one->sha1_valid && two->sha1_valid &&
	    !hashcmp(one->sha1, two->sha1) &&
	if (!one->sha1_valid && !two->sha1_valid)
		s->sha1_valid ? sha1_to_hex(s->sha1) : "");
	fprintf(stderr, "queue[%d] %s size %lu flags %d\n",
		s->size, s->xfrm_flags);
		else if (hashcmp(p->one->sha1, p->two->sha1) ||
			 is_null_sha1(p->one->sha1))
	char *line_prefix = "";

	if (opt->output_prefix) {
		struct strbuf *buf = opt->output_prefix(opt, opt->output_prefix_data);
		line_prefix = buf->buf;
	}
	if (!prefixcmp(line, "@@ -"))
static int diff_get_patch_id(struct diff_options *options, unsigned char *sha1)
	char buffer[PATH_MAX * 4 + 20];
		diff_fill_sha1_info(p->one);
		diff_fill_sha1_info(p->two);
		if (fill_mmfile(&mf1, p->one) < 0 ||
				fill_mmfile(&mf2, p->two) < 0)
			return error("unable to read files to diff");
		if (p->one->mode == 0)
			len1 = snprintf(buffer, sizeof(buffer),
					"diff--gita/%.*sb/%.*s"
					"newfilemode%06o"
					"---/dev/null"
					"+++b/%.*s",
					len1, p->one->path,
					len2, p->two->path,
					p->two->mode,
					len2, p->two->path);
		else if (p->two->mode == 0)
			len1 = snprintf(buffer, sizeof(buffer),
					"diff--gita/%.*sb/%.*s"
					"deletedfilemode%06o"
					"---a/%.*s"
					"+++/dev/null",
					len1, p->one->path,
					len2, p->two->path,
					p->one->mode,
					len1, p->one->path);
		else
			len1 = snprintf(buffer, sizeof(buffer),
					"diff--gita/%.*sb/%.*s"
					"---a/%.*s"
					"+++b/%.*s",
					len1, p->one->path,
					len2, p->two->path,
					len1, p->one->path,
					len2, p->two->path);
		git_SHA1_Update(&ctx, buffer, len1);
			git_SHA1_Update(&ctx, sha1_to_hex(p->one->sha1), 40);
			git_SHA1_Update(&ctx, sha1_to_hex(p->two->sha1), 40);
		xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
			      &xpp, &xecfg);
	git_SHA1_Final(sha1, &ctx);
int diff_flush_patch_id(struct diff_options *options, unsigned char *sha1)
	int result = diff_get_patch_id(options, sha1);
"inexact rename detection was skipped due to too many files.";
"only found copies from modified paths due to too many files.";
"you may want to set your %s variable to at least "
"%d and retry the command.";
		warning(degrade_cc_to_c_warning);
		warning(rename_limit_warning);
		warning(rename_limit_advice, varname, needed);
		if (output_format & DIFF_FORMAT_DIRSTAT)
		 * options->file to /dev/null should be safe, becaue we
		options->file = fopen("/dev/null", "w");
		if (!options->file)
			die_errno("Could not open /dev/null");
			if (options->output_prefix) {
				struct strbuf *msg = NULL;
				msg = options->output_prefix(options,
					options->output_prefix_data);
				fwrite(msg->buf, msg->len, 1, stdout);
			}
			putc(options->line_termination, options->file);
static void diffcore_apply_filter(const char *filter)
	if (!filter)
	if (strchr(filter, DIFF_STATUS_FILTER_AON)) {
			struct diff_filepair *p = q->queue[i];
			if (((p->status == DIFF_STATUS_MODIFIED) &&
			     ((p->score &&
			       strchr(filter, DIFF_STATUS_FILTER_BROKEN)) ||
			      (!p->score &&
			       strchr(filter, DIFF_STATUS_MODIFIED)))) ||
			    ((p->status != DIFF_STATUS_MODIFIED) &&
			     strchr(filter, p->status)))

			if (((p->status == DIFF_STATUS_MODIFIED) &&
			     ((p->score &&
			       strchr(filter, DIFF_STATUS_FILTER_BROKEN)) ||
			      (!p->score &&
			       strchr(filter, DIFF_STATUS_MODIFIED)))) ||
			    ((p->status != DIFF_STATUS_MODIFIED) &&
			     strchr(filter, p->status)))
		/*
		 * 1. Entries that come from stat info dirtiness
		 *    always have both sides (iow, not create/delete),
		 *    one side of the object name is unknown, with
		 *    the same mode and size.  Keep the ones that
		 *    do not match these criteria.  They have real
		 *    differences.
		 *
		 * 2. At this point, the file is known to be modified,
		 *    with the same mode and size, and the object
		 *    name of one side is unknown.  Need to inspect
		 *    the identical contents.
		 */
		if (!DIFF_FILE_VALID(p->one) || /* (1) */
		    !DIFF_FILE_VALID(p->two) ||
		    (p->one->sha1_valid && p->two->sha1_valid) ||
		    (p->one->mode != p->two->mode) ||
		    diff_populate_filespec(p->one, 1) ||
		    diff_populate_filespec(p->two, 1) ||
		    (p->one->size != p->two->size) ||
		    !diff_filespec_is_identical(p->one, p->two)) /* (2) */
	qsort(q->queue, q->nr, sizeof(q->queue[0]), diffnamecmp);
	diffcore_apply_filter(options->filter);
	diff_warn_rename_limit("diff.renamelimit",
		    const unsigned char *sha1,
		fill_filespec(one, sha1, mode);
		fill_filespec(two, sha1, mode);
		 const unsigned char *old_sha1,
		 const unsigned char *new_sha1,
		unsigned tmp;
		const unsigned char *tmp_c;
		tmp = old_mode; old_mode = new_mode; new_mode = tmp;
		tmp_c = old_sha1; old_sha1 = new_sha1; new_sha1 = tmp_c;
		tmp = old_dirty_submodule; old_dirty_submodule = new_dirty_submodule;
			new_dirty_submodule = tmp;
	fill_filespec(one, old_sha1, old_mode);
	fill_filespec(two, new_sha1, new_mode);
	diff_queue(&diff_queued_diff, one, two);
	if (!DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		DIFF_OPT_SET(options, HAS_CHANGES);
	struct child_process child;
	memset(&child, 0, sizeof(child));
	if (!driver || !driver->textconv) {
	if (driver->textconv_cache && df->sha1_valid) {
		*outbuf = notes_cache_get(driver->textconv_cache, df->sha1,
	if (driver->textconv_cache && df->sha1_valid) {
		notes_cache_put(driver->textconv_cache, df->sha1, *outbuf,