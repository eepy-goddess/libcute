# Libcute Contribution Guidelines

## Libcute Naming Convention
1. All functions must be snake_case and have `cute_` as a prefix.
2. Structs need to be CamelCased with the first letter capitalized.
3. All function declarations in header files need to have the `extern` keyword if they are intended to be defined outside of the header file in which it was declared.
4. Variables, whether they are global or local, have to have snake_cased names, same with parameter names. **No one-letter variable or parameter names are allowed**.
5. Constants and macro definitions need to be in SCREAMING_SNAKE_CASE format.
6. Enum names need to be CamelCased with the first letter capitalized, and enum values need to be SCREAMING_SNAKE_CASE.
7. On conditional macros, `#endif`s and `#else`s need to have a single-line comment after them that contains the condition of their corresponding `#if` or `#ifdef`/`#ifndef`.

## How to Contribute and Pull Request
If you aren't a maintainer, you need to fork the repository. Once you fork the repository, make your changes, then make sure the changes abide by the guidelines
above. If you are confident that they abide by the guidelines, then you can now make a pull request.

If you are a maintainer, you can make a branch, preferably with a name that is related to the thing that you're working on. Once the branch is made, you
can make your changes there. Also make sure that your changes abide to the guidelines above.

Merging a pull request to the `main` branch requires:
1. You pass the checks that are ran when you make the pull request. If you don't pass, then there is a good chance that your code has an error, so please fix it.
2. Your commits need to be signed with your verified signature. If you are unsure on how to sign commits, here is a guide on how to [sign them](https://docs.github.com/en/authentication/managing-commit-signature-verification/about-commit-signature-verification).
3. An approved review by a maintainer.
4. your branch/fork must be up-to-date.

## Maintainers
So far, I(Astrid) am the only maintainer lmao. These are people who have authority to merge pull requests(if the pull request prerequisites are met).
Contact the maintainers if you have any criticisms on the project. **PLEASE** don't mention(@) them on a pull request or issue that is less than 2 days old. We will try our best to review all pull requests and issues as soon as possible.
1. Astrid(a-weeb-programmer), discord: `a weeb programmer#6958`
