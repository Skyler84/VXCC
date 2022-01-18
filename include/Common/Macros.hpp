/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */


#define CALL(x, y...) x(y)
#define CALL__(x, y...) x(y)
#define CALL_ARGS_1(x, y...) CALL__(SEQ(FIRST, y), x, SEQ(SECOND, y))
#define CALL_ARGS_2(x, y...)CALL__(SEQ(FIRST, y), x, SEQ(SECOND, y), SEQ(THIRD(y)))

#define FIRST(x, ...) x
#define SECOND(x, ...) FIRST(__VA_ARGS__)
#define THIRD(x, ...) SECOND(__VA_ARGS__)
#define TO_FIRST(x, ...) x
#define TO_SECOND(x, ...) x, FIRST(__VA_ARGS__)
#define TO_THIRD(x, ...) x, SECOND(__VA_ARGS__)
#define DROP_FIRST(x, ...) __VA_ARGS__
#define DROP_SECOND(x, ...) x, DROP_DROP_FIRST(__VA_ARGS__)
#define DROP_THIRD(x, ...) x, DROP_SECOND(__VA_ARGS__)
#define DROP_TO_FIRST(x, ...) __VA_ARGS__
#define DROP_TO_SECOND(x, ...) __VA_ARGS__
#define DROP_TO_THIRD(x, ...) __VA_ARGS__
#define EXPAND(...) __VA_ARGS__
#define REMOVE_PAREN(x) SEQ(EXPAND, x)
#define EXPAND_PLUS_BEFORE(y, ...) __VA_ARGS__, SEQ(EXPAND, y)
#define EXPAND_PLUS_AFTER(y, ...) SEQ(EXPAND, y), __VA_ARGS__
#define ADD_ARG_BEFORE(y, ...) (__VA_ARGS__, REMOVE_PAREN(y))
#define ADD_ARG_AFTER(y, ...) (REMOVE_PAREN(y), __VA_ARGS__)
#define EVAL(x...) x
#define SEQ(x, y) x y
#define RSEQ(x, y) y x
#define CONCAT(x, y) x##y
#define RCONCAT(x, y) y##x
#define WRAP(a, x, y) x##a##y
#define CONCAT_ARG(x, y)
#define CONCAT_ARG_1(x, y) CALL__1(CONCAT, x, SEQ(FIRST, y))
#define CONCAT_ARG_2(x, y) CALL__1(CONCAT, x, SEQ(SECOND, y))
#define CONCAT_ARG_3(x, y) CALL__1(CONCAT, x, SEQ(THIRD, y))
#define COMMA(x, ...) x,

#define ALIAS_8(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_9(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_7(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_8(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_6(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_7(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_5(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_6(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_4(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_5(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_3(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_4(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_2(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_3(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_1(n, o, p, x, ...) __VA_OPT__(o(n(FIRST(__VA_ARGS__), p) = n(x, p), p) ALIAS_2(n, o, p, x, DROP_FIRST(__VA_ARGS__)))
#define ALIAS_ALL(n, o, p, x, ...) __VA_OPT__(ALIAS_1(n, o, p, x, __VA_ARGS__))
#define ALIAS(n, o, p, x, ...) o(n(x, p), p) ALIAS_ALL(n, o, p, x, __VA_ARGS__)
#define _ALIAS(...) ALIAS(__VA_ARGS__)
/**
 *  @brief creates alias definitions - o(a) o(b=a) o(c=a) ...
 *  Takes four parameters.
 *  @param n modifier callback macro - alter token
 *  @param o definition callback macro - usually used to add comma
 *  @param p data for callback macros
 *  @param x alias identifiers - paren enclosed list (a, b, c...)
 */
#define ALIASES(n, o, p, x) _ALIAS(EXPAND_PLUS_BEFORE(x, n, o, p))
#define ALIASES_NOMOD(aliases) ALIASES(FIRST, COMMA, (), aliases)
#define ALIASES_CONCAT(aliases, cat) ALIASES(CALL_ARGS_1, COMMA, (CONCAT, cat), aliases)
#define ALIASES_RCONCAT(aliases, rcat) ALIASES(CALL_ARGS_1, COMMA, (RCONCAT, rcat), aliases)
#define ALIASES_WRAP(aliases, left, right) ALIASES(CALL_ARGS_2, COMMA, (WRAP, left, right), aliases)

