	struct combine_diff_path *p;
	int i;
		struct combine_diff_path *list = NULL, **tail = &list;
			p->len = len;
			hashcpy(p->sha1, q->queue[i]->two->sha1);
			hashcpy(p->parent[n].sha1, q->queue[i]->one->sha1);
		return list;
	for (p = curr; p; p = p->next) {
		int found = 0;
		if (!p->len)
		for (i = 0; i < q->nr; i++) {
			const char *path;
			int len;
			if (diff_unmodified_pair(q->queue[i]))
				continue;
			path = q->queue[i]->two->path;
			len = strlen(path);
			if (len == p->len && !memcmp(path, p->path, len)) {
				found = 1;
				hashcpy(p->parent[n].sha1, q->queue[i]->one->sha1);
				p->parent[n].mode = q->queue[i]->one->mode;
				p->parent[n].status = q->queue[i]->status;
				break;
			}
		if (!found)
			p->len = 0;
	struct lline *next;
	struct lline *lost_head, **lost_tail;
	struct lline *next_lost;
static char *grab_blob(const unsigned char *sha1, unsigned int mode,
		blob = xmalloc(100);
		*size = snprintf(blob, 100,
				 "Subproject commit %s\n", sha1_to_hex(sha1));
	} else if (is_null_sha1(sha1)) {
		fill_filespec(df, sha1, mode);
		blob = read_sha1_file(sha1, &type, size);
			die("object '%s' is not a blob!", sha1_to_hex(sha1));
	/* Check to see if we can squash things */
	if (sline->lost_head) {
		lline = sline->next_lost;
		while (lline) {
			if (lline->len == len &&
			    !memcmp(lline->line, line, len)) {
				lline->parent_map |= this_mask;
				sline->next_lost = lline->next;
				return;
			}
			lline = lline->next;
		}
	}

	lline = xmalloc(sizeof(*lline) + len + 1);
	memcpy(lline->line, line, len);
	lline->line[len] = 0;
	*sline->lost_tail = lline;
	sline->lost_tail = &lline->next;
	sline->next_lost = NULL;
		state->lost_bucket->next_lost = state->lost_bucket->lost_head;
static void combine_diff(const unsigned char *parent, unsigned int mode,
			 const char *path)
	xpp.flags = 0;
	xdi_diff_outf(&parent_file, result_file, consume_line, &state,
		      &xpp, &xecfg);
		ll = sline[lno].lost_head;
	return ((sline->flag & all_mask) || sline->lost_head);
		while (j < i)
			sline[j++].flag |= mark | no_pre_delete;
			struct lline *ll = sline[j].lost_head;
static void dump_sline(struct sline *sline, unsigned long cnt, int num_parent,
	const char *c_plain = diff_get_color(use_color, DIFF_PLAIN);
		fputs(c_frag, stdout);
						    c_plain, c_reset,
			ll = (sl->flag & no_pre_delete) ? NULL : sl->lost_head;
				fputs(c_old, stdout);
				fputs(c_plain, stdout);
		struct lline *ll = sline->lost_head;
	int abbrev = DIFF_OPT_TST(opt, FULL_INDEX) ? 40 : DEFAULT_ABBREV;
			 "", elem->path, c_meta, c_reset);
	printf("%sindex ", c_meta);
		abb = find_unique_abbrev(elem->parent[i].sha1,
	abb = find_unique_abbrev(elem->sha1, abbrev);
			printf("%snew file mode %06o",
			       c_meta, elem->mode);
				printf("%sdeleted file ", c_meta);
				 c_meta, c_reset);
				 c_meta, c_reset);
				 c_meta, c_reset);
				 c_meta, c_reset);
		result = grab_blob(elem->sha1, elem->mode, &result_size,
				error("readlink(%s): %s", elem->path,
				      strerror(errno));
			unsigned char sha1[20];
			if (resolve_gitlink_ref(elem->path, "HEAD", sha1) < 0)
				result = grab_blob(elem->sha1, elem->mode,
				result = grab_blob(sha1, elem->mode,
			fill_filespec(df, null_sha1, st.st_mode);
			result = xmalloc(len + 1);
			result[len] = 0;

				if (convert_to_git(elem->path, result, len, &buf, safe_crlf)) {
			buf = grab_blob(elem->parent[i].sha1,
				     mode_differs, 0);
	sline = xcalloc(cnt+2, sizeof(*sline));
	for (lno = 0; lno <= cnt + 1; lno++) {
		sline[lno].lost_tail = &sline[lno].lost_head;
		sline[lno].flag = 0;
	}
	sline[0].p_lno = xcalloc((cnt+2) * num_parent, sizeof(unsigned long));
			if (!hashcmp(elem->parent[i].sha1,
				     elem->parent[j].sha1)) {
			combine_diff(elem->parent[i].sha1,
				     textconv, elem->path);
				     mode_differs, 1);
		dump_sline(sline, cnt, num_parent,
		if (sline[lno].lost_head) {
			struct lline *ll = sline[lno].lost_head;
#define COLONS "::::::::::::::::::::::::::::::::"

	int i, offset;
	const char *prefix;
	int line_termination, inter_name_termination;
		offset = strlen(COLONS) - num_parent;
		if (offset < 0)
			offset = 0;
		prefix = COLONS + offset;
		for (i = 0; i < num_parent; i++) {
			printf("%s%06o", prefix, p->parent[i].mode);
			prefix = " ";
		}
		printf("%s%06o", prefix, p->mode);
			printf(" %s", diff_unique_abbrev(p->parent[i].sha1,
							 opt->abbrev));
		printf(" %s ", diff_unique_abbrev(p->sha1, opt->abbrev));
	if (!p->len)
		return;
	pool = xcalloc(num_parent + 1, sizeof(struct diff_filespec));
		hashcpy(pair->one[i].sha1, p->parent[i].sha1);
		pair->one[i].sha1_valid = !is_null_sha1(p->parent[i].sha1);
	hashcpy(pair->two->sha1, p->sha1);
	pair->two->sha1_valid = !is_null_sha1(p->sha1);
	for (i = 0, p = paths; p; p = p->next) {
		if (!p->len)
			continue;
	}
void diff_tree_combined(const unsigned char *sha1,
			const struct sha1_array *parents,
	struct combine_diff_path *p, *paths = NULL;
	diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
	show_log_first = !!rev->loginfo && !rev->no_commit_id;
	needsep = 0;
	/* find set of paths that everybody touches */
	for (i = 0; i < num_parent; i++) {
		/* show stat against the first parent even
		int stat_opt = (opt->output_format &
		if (i == 0 && stat_opt)
		else
			diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
		diff_tree_sha1(parents->sha1[i], sha1, "", &diffopts);
		diffcore_std(&diffopts);
		paths = intersect_paths(paths, i, num_parent);
		if (show_log_first && i == 0) {
			show_log(rev);
			if (rev->verbose_header && opt->output_format)
				putchar(opt->line_termination);
		diff_flush(&diffopts);
	/* find out surviving paths */
	for (num_paths = 0, p = paths; p; p = p->next) {
		if (p->len)
			num_paths++;
			for (p = paths; p; p = p->next) {
				if (p->len)
					show_raw_diff(p, num_parent, rev);
			}
				putchar(opt->line_termination);
			for (p = paths; p; p = p->next) {
				if (p->len)
					show_patch_diff(p, num_parent, dense,
							0, rev);
			}
	struct commit_list *parent = commit->parents;
	struct sha1_array parents = SHA1_ARRAY_INIT;
		sha1_array_append(&parents, parent->item->object.sha1);
	diff_tree_combined(commit->object.sha1, &parents, dense, rev);
	sha1_array_clear(&parents);