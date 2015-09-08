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
communication has been cut off, but you may or may not have brought up to
3 friends along with you, each a specialist in a different type of weaponry.
Just when you think things couldn't get any worse, you realize that your
surrounding area is filled with junk. Survive as long as you can by avoiding and
shooting the asteroids until your inevitable demise!

================================================================================
Known Issues:
================================================================================

I only had access to 2 controllers, so although I did my best to check and
test multiplayer support, anything with 3 to 4 players may crash, as I haven't
been able to debug any of it.

================================================================================
How to Use:
================================================================================

Keyboard Controls (Player 1 only):
W - Thrust forward
A - Rotate counterclockwise
D - Rotate clockwise
O - Add an asteroid
L - Remove an asteroid
G - Toggle extra debugging information
P - Respawn your ship
Esc - Exit the program

Xbox Controller Controls:
Left Stick - Rotate Ship
Right Trigger - Thrust forward
A - Fire weapon
Start - Respawn your ship

Use the A and D keys to rotate your ship, and W to thrust in a direction.
Avoid the asteroids for as long as you can. Press O to add additional asteroids
for an extra challenge, and L to remove asteroids for easier gameplay. If you
die, press P to try again.

================================================================================
Extra Features and Polish:
================================================================================

COOPERATIVE MULTIPLAYER:
Attach up to 4 Xbox controllers to play with friends and family. Plugging in
a controller will spawn a ship for that player, and removing the controller will
remove that ship from play. The first controller correlates to the Keyboard
player, and controls the same ship (As per the requirements).

MULTIPLAYER CLASSES / WEAPONS:
Each of the players is given a particular weapon for their ship, which impacts
how the player plays the game. The four weapons are as follows:
	P1: Standard gun. Fires a single shot straight ahead. Well-rounded, the
      gun featured in classic Asteroids.
  P2: Shotgun. Fires an inaccurate burst that does lots of damage, but has
      extremely limited range.
  P3: V gun. Shoots two bullets 45 degrees off-center. Keen positioning and
      spacing between asteroids will help this player succeed.
  P4: Velocity gun. The faster you go, the faster your bullets go. Encourages
      high-risk, high-reward play. Gotta go fast.

XBOX CONTROLLER VIBRATION:
Holding down the thrust will increase your rumble based on how hard you hold
the trigger. The rumble uses the right motor, which gives a gentle vibration
that ramps up in intensity as you squeeze the trigger harder. If you collide
with an asteroid, you'll experience a brief, high-intensity rumble as you
watch your ship explode.

DEBUG MODE:
Press G if you'd like to see some interesting debugging information.
Here's the breakdown for what you'll find drawn to each entity on screen:
  => Cyan Dot: Object's position
  => Red Circle: Physical Radius / Hitbox
  => Green Circle: Cosmetic Radius
  => Yellow Line: Orientation of the object

MINOR AESTHETICAL CHANGES:
  - Bullets start off red and fade to yellow depending on their lifespan
  - The ship explodes and shrinks as it dies
  - Asteroids are procedurally generated every time a new one breaks off or is
    spawned at the start of a wave
  - Uniquely colored ships for each player
  - Thrusting animation cycles from Red to Orange to Yellow based on time

================================================================================
Deep Learning:
================================================================================

During this session, I noticed code bloating as I added and revised the
new features that we needed to add. I had initially felt pretty good about
my code from Asteroids 1, but as I continued writing more and more, my Update
and Render methods began to expand. Each new feature I added required more
and more resources, attention, and special treatment. A system that worked
perfectly for controlling the ship doubled in size as I attempted to integrate
Xbox controller support. As I went along, I tried my best to reduce some of
the more complicated parts and break them out into their own functions. I now
understand more thoroughly the need for constant refactoring, and I strive to
use this knowledge to my advantage. I want to focus on catching the bloating
issues more quickly than I have in the past, and I strive to keep learning the
best ways to break up and organize huge chunks of code into logical groupings.
