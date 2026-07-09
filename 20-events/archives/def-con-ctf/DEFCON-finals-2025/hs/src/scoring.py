import yaml
import logfire
import sqlite3
from contextlib import contextmanager

ALL_PROMPTS = yaml.safe_load(open("prompts.yaml"))

@contextmanager
def get_db():
    conn = sqlite3.connect('game_status.db')
    conn.row_factory = sqlite3.Row
    try:
        yield conn
        conn.commit()
    except:
        conn.rollback()
        raise
    finally:
        conn.close()

def init_db():
    with get_db() as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS team_solves (
                team TEXT,
                prompt TEXT,
                solved BOOLEAN DEFAULT 0,
                PRIMARY KEY (team, prompt)
            )
        ''')

def init_team(team: str):
    print(f"Initializing team {team}")
    logfire.info(f"Initializing team {team}")
    with get_db() as conn:
        for prompt in ALL_PROMPTS:
            conn.execute(
                'INSERT OR IGNORE INTO team_solves (team, prompt) VALUES (?, ?)',
                (team, prompt)
            )

def get_next_prompt(team: str) -> str | None:
    with get_db() as conn:
        # Ensure team exists
        result = conn.execute('SELECT COUNT(*) FROM team_solves WHERE team = ?', (team,)).fetchone()
        if result[0] == 0:
            init_team(team)

        # Get first unsolved prompt
        result = conn.execute('''
            SELECT prompt FROM team_solves 
            WHERE team = ? AND solved = 0 
            ORDER BY prompt
            LIMIT 1
        ''', (team,)).fetchone()

        return result['prompt'] if result else None

def set_prompt_solved(team: str, prompt: str):
    print(f"Setting prompt {prompt} as solved for team {team}")
    with get_db() as conn:
        conn.execute(
            'UPDATE team_solves SET solved = 1 WHERE team = ? AND prompt = ?',
            (team, prompt)
        )

# Initialize database on import
init_db()
