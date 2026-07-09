# Adding New Utility

Slither can be used as a library to create new utilities.
Official utils are present in [tools](https://github.com/crytic/slither)

## Skeleton

The skeleton util is present in [tools/demo](https://github.com/crytic/slither)

## Integration

To enable an util from the command-line, update `project.scripts` in [pyproject.toml](https://github.com/crytic/slither).
Installing Slither will then install the util.

## Guidelines

- Favor the `logging` module rather than `print`
- Favor raising an exception rather than `sys.exit`
- Add unit-tests (ex: [scripts/travis_test_find_paths.sh](https://github.com/crytic/slither))

## Getting Help

Join our [slack channel](https://empireslacking.herokuapp.com/) to get any help (#ethereum).
