## What's this?

An attempt to "crack" the PIN number of the hidden flash recovery page of the Arcadyan/Astoria VGV7519 modem/router,
also known as the KPN Experia Box v8.

From disassembling the firmware, only the SHA-1 hash of the PIN number was obtained, which was documented at
https://openwrt.org/toh/arcadyan/vgv7519.

Specifically, it pertains to the following mysterious SHA-1 hash:

```text
B16D0EF3 DD0632DC D13D135E 02A097AE C4044C24
```

Since it the recovery page apparently asked for a "PIN number", I figured it would likely be a numeric password, and
therefore relavely easy to crack. (That turned out to be too optimistic. Keep reading.)

So I figured I just write something that would generate SHA-1 hashes from a range of PIN number, starting at 0 and going
as high as defined in the const `max_number`.

To be safe, it would check the has both with and without leading zeroes.

The bad news: I was unable to find a PIN number with the matching SHA-1 hash, even when I modified it to search for
hexadecimal numbers as well. (I tried both lower case and uppercase until it had tried numbers well into the 7 digits.)

The good news: this challenge gave me me some practice in dusting off my C programming skills, which are  a bit rusty
(heh, no pun intended, but indeed, I've actually been dabbling in Rust as well!).

Note that by default, the "magic" hash from the OpenWrt wiki that we're looking for is greyed out, in favor of the hash
of the string "1234". That one is therefore used by default, as a means to test the code. To actually search for the
VGV7519 PIN hash, uncomment the correct `sha1_hash_to_decode_in_hex` definition line and comment out the other
(`"1234"`) one. Or, if you wish, paste in another SHA-1 hash that you happen to be looking for.

Sharing this here, in case it's useful to someone else. If nothing else, it makes it clear how easy and fast it is to
build rainbow tables, especially when using outdated hashes such as SHA-1. So remember, kids: always use a more secure
hashing algorithm, and don't forget to use salts as well! 🙂

I happen to be pushing this to GitHub on Christmas, so Merry Christmas, everyone. 🎄