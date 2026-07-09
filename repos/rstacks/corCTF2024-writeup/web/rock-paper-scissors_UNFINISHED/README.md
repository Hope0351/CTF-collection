# rock-paper-scissors

## Description

can you beat fizzbuzz at rock paper scissors?

## Attachments

[rock-paper-scissors.tar.gz](attachments/rock-paper-scissors.tar.gz)

## Solution (Unfinished)

- The provided website is a rock paper scissors game. We are able to select a move to play,
and the computer randomly picks its own move. Our score increases every time we beat the computer.

- Analyzing the provided attachment reveals this in <code>index.js</code>:

```
app.get('/flag', async (req, res) => {
	try {
		await req.jwtVerify();
	} catch(e) {
		return res.status(400).send({ error: 'invalid token' });
	}
	const score = await redis.zscore('scoreboard', req.user.username);
	if (score && score > 1336) {
		return res.send(process.env.FLAG || 'corctf{test_flag}');
	}
	return res.send('You gotta beat Fizz!');
});
```
- If our score is greater than 1336, then sending a GET request to <code>/flag</code> will reveal
the flag. After playing a game against the computer, a POST request is made to <code>/play</code> to
set the score appropriately, as shown in <code>index.js</code>:

```
app.post('/play', async (req, res) => {
	try {
		await req.jwtVerify();
	} catch(e) {
		return res.status(400).send({ error: 'invalid token' });
	}
	const { game, username } = req.user;
	const { position } = req.body;
	const system = ['🪨', '📃', '✂️'][randomInt(3)];
	if (winning.get(system) === position) {
		const score = await redis.incr(game);

		return res.send({ system, score, state: 'win' });
	} else {
		const score = await redis.getdel(game);
		if (score === null) {
			return res.status(404).send({ error: 'game not found' });
		}
		await redis.zadd('scoreboard', score, username);
		return res.send({ system, score, state: 'end' });
	}
});
```

- My idea was to send a ton of POST requests to <code>/play</code> in an attempt to get my score past 1336. I would then access <code>/flag</code> to get the flag.

- I intercepted one of the post-game POST requests with [Burp Suite](https://portswigger.net/burp/communitydownload) to see how it was formatted. Then,
I wrote a [Python script](winner.py) to send POST requests repeatedly with the same rock paper scissors move 
believing that this would eventually result in enough wins to see the flag. Unfortunately,
I was not able to get the flag this way.
