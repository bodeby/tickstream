# tickstream

[![CI](https://github.com/bodeby/tickstream/actions/workflows/ci.yml/badge.svg)](https://github.com/bodeby/tickstream/actions/workflows/ci.yml)

[![CodeQL](https://github.com/bodeby/tickstream/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/bodeby/tickstream/actions/workflows/github-code-scanning/codeql)

header-only library for simulating asset movements

### Micro Structure

```
tickstream/include/tickstream/stream_gen.hpp    # public
tickstream/include/tickstream/detail/models.hpp # private
```


### Concepts

- [Ring Buffer](https://en.wikipedia.org/wiki/Circular_buffer)