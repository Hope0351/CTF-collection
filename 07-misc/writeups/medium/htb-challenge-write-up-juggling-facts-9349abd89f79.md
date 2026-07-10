# :game_die: HTB Challenge Write-Up: Juggling Facts

---

# HTB Challenge Write-Up: Juggling Facts

## Code Review

Juggling Facts is a website featuring “not-so-spooky” facts about pumpkins. It is written in PHP, a loosely typed language. Given the challenge’s title, it most likely contains a *Type Juggling* vulnerability. Let’s dive deeper.

Upon reviewing the code, the flag can be retrieved by querying the database through the `/api/getfacts` endpoint. However, a few conditions must be met to access the code that interacts with the database.

```
if ( empty($jsondata) || !array_key_exists('type', $jsondata))
{
return $router->jsonify(['message' => 'Insufficient parameters!']);
}

if ($jsondata['type'] === 'secrets' && $_SERVER['REMOTE_ADDR'] !== '127.0.0.1')
{
return $router->jsonify(['message' => 'Currently this type can be only accessed through localhost!']);
}
```

Given these conditions, our payload must (1) be a JSON object containing a `type` field, and (2) ensure the `type` field's value is NOT a string equal to `"secrets"`.

## Get Pat Bautista’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Sounds easy, right? But there’s a problem. To retrieve the database entry containing the flag, the `type` value must be a string equal to `"secret"`. This directly conflicts with the second condition our payload must satisfy.

```
switch ($jsondata['type'])
{
case 'secrets':
return $router->jsonify([
'facts' => $this->facts->get_facts('secrets')
]);

// code omitted for brevity
}
```

We’re faced with two conflicting conditions that need to be met to retrieve the flag. The first condition uses strict comparison (`===`), so the second one, which uses a `switch/case` statement, must be loose, right? There’s one way to find out—Google it.

That confirms it! The official PHP documentation reveals that `switch/case` uses a loose comparison. This is a clear case of Type Juggling.

## Local Testing

Since the code doesn’t include a type check, let’s consult PHP’s loose comparison table to determine which other data types can be compared to a string for the condition to be true.

According to the table, when a non-empty string is loosely compared with the boolean value `true`, the result will be `true`. Let’s confirm this by using the PHP interactive shell (type `php -a` in the terminal).

## Exploitation

Now that we’ve confirmed we can use the boolean value `true` with a non-empty string to trigger Type Juggling, we can leverage this to match the first case of the `switch/case` statement, which happens to be the one that retrieves the flag.

Using `curl`, we’ll send the JSON payload `{"type":true}` to the `/api/getfacts` endpoint. Notice that the value `true` doesn’t have double quotes, so it will be parsed as a boolean.

This successfully retrieves the flag.

## References

---
