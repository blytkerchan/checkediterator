# Checked Output Iterator
The checkediterator.hpp file contains a simple checked output iterator: it will 
throw a range_error when dereferenced while invalid or incremented when at the
end.

You can easily construct a checked output iterator using the 
`makeCheckedOutputIterator` function. You can pass it either an array (i.e. 
`makeCheckedOutputIterator(a)`) or a pair of iterators
(`makeCheckedOutputIterator(v.begin(), v.end())`). In either case, it will 
return a single output iterator with knowledge of where the end of the valid
range is.

The overhead, when inlined, is really very small: it adds an if and a comparison
for each dereference or increment -- a small price to pay for the extra safety
it affords.