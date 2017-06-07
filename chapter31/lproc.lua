--[ exercise 31.2 ]--

local lproc = require "liblproc"
lproc.start("print(liblproc.recv('channel'))")
lproc.send('channel', 'hello', 'world', 1, 2, true)
lproc.exit()
