_______  _______  _______  _______  ______    _______  ___   ______   _______
|   _   ||       ||       ||       ||    _ |  |       ||   | |      | |       |
|  |_|  ||  _____||_     _||    ___||   | ||  |   _   ||   | |  _    ||  _____|
|       || |_____   |   |  |   |___ |   |_||_ |  | |  ||   | | | |   || |_____
|       ||_____  |  |   |  |    ___||    __  ||  |_|  ||   | | |_|   ||_____  |
|   _   | _____| |  |   |  |   |___ |   |  | ||       ||   | |       | _____| |
|__| |__||_______|  |___|  |_______||___|  |_||_______||___| |______| |_______|

The spaceyear is 30XX. You are a cosmonaut in a NODESTAR model fighter ship.
You were traveling along with your single file convoy when a software error
caused you to warp deep into unallocated space. Your single link of
communication has been cut off, and your weapon pointers are now garbage.
Just when you think things couldn't get any worse, you realize that your
surrounding area is filled with junk. Survive as long as you can by avoiding the
asteroids until you overstep your bounds and crash.

================================================================================
Known Issues:
================================================================================
N/A

================================================================================
How to Use:
================================================================================
W - Thrust forward
A - Rotate counterclockwise
D - Rotate clockwise
O - Add an asteroid
L - Remove an asteroid
G - Toggle extra debugging information
P - Respawn the ship
Esc - Exit the program

Use the A and D keys to rotate your ship, and W to thrust in a direction.
Avoid the asteroids for as long as you can. Press O to add additional asteroids
for an extra challenge, and L to remove asteroids for easier gameplay. If you
die, press P to try again.

Press G if you'd like to see some interesting debugging information.
Here's the breakdown for what you'll find on screen:
  => Cyan Dot: Object's position
  => Red Circle: Physical Radius / Hitbox
  => Green Circle: Cosmetic Radius


================================================================================
Deep Learning:
================================================================================

I've known that uninitialized variables cause problems, but it wasn't until
this project that I began to realize the significance of initializing variables
immediately after you write them. I had just finished writing the code that
updated orientation based on angular velocity and ran my game, when I was
greeted with my ship spinning wildly out of control. I immediately realized
that this meant my angular velocity was uninitialized, and defaulted to a large
garbage value. I also realized that before taking this class, I
wouldn't have come to this conclusion immediately, and that I would have
wasted a bunch of time poking around for the error instead. From now on, I'll
try and adopt the approach of "feeling uneasy until you've initialized your
new variable", and attempt to be more conscious of when I'm creating
variables. It's far too easy for me to think of writing the declaration and
initialization as two different steps instead of as one atomic action, and I'd
like to change that as I progress through this class.
