mkdir -p tests/files
echo "test
This is a tet file
abcdefg
123test456
test123d
äü" > tests/files/in

echo "no permissions" > tests/files/no_perm
chmod 000 tests/files/no_perm