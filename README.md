Pong game recreated using C and SDL.

TODO:
- Ball Movement and bouncing.
    - Law of Reflection.
        - R = V - 2 * (V * N) * N
        - R: New direction
        - V: Incoming velocity vector
        - N: Normal vector of the surface (the edge of the paddle.)
        - V * N: Dot product between V and N
- Render out the text and background line.
- Track score.
- Win Lose Conditions.
- Start menu?
- Networking Multiplayer.
- Dedicated Server & Peer to Peer
- I wonder if I should include walls as a new structure type. I can make them dark gray. This helps visibility of the boundaries. It can also be nice to use for collision for paddles and ball. And it makes it easy to change boundaries.
