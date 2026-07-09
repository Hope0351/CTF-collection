import pytest
import os
import sys
import pwn

# Enable pwntools logging to see all I/O
# Options: 'debug', 'info', 'warn', 'error', 'critical'
# pwn.context.log_level = 'debug'  

# Add the tests directory to the path so we can import x
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import x

@pytest.fixture
def jukebox_connection():
    """Create a fresh connection to the jukebox for each test."""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    conn = pwn.process(f"{script_dir}/../build/jukebooox", stdin=pwn.PTY, stdout=pwn.PTY)
    
    # Wait for the initial prompt
    conn.readuntil(b"Would you like to play a song")
    yield conn
    
    # Cleanup: send quit command
    try:
        x.quit(conn)
        conn.clean()
    except:
        pass
    finally:
        conn.kill()
        print("Done")

class TestUploadSong:
    """Test cases for the upload_song functionality."""
    
    def test_upload_valid_wav_file(self, jukebox_connection):
        """Test uploading a valid WAV file."""
        script_dir = os.path.dirname(os.path.abspath(__file__))
        with open(f"{script_dir}/data/test_8bit.wav", "rb") as f:
            wav_data = f.read()
        
        x.upload_song(jukebox_connection, b"test_song\n", wav_data)
        
        # Check that the upload was successful by looking for the menu again
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_upload_different_wav_file(self, jukebox_connection):
        """Test uploading a different WAV file."""
        script_dir = os.path.dirname(os.path.abspath(__file__))
        with open(f"{script_dir}/data/test_simple.wav", "rb") as f:
            wav_data = f.read()

        x.upload_song(jukebox_connection, b"test_song_simple\n", wav_data)
        
        # Check that the upload was successful
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_upload_empty_file(self, jukebox_connection):
        """Test uploading an empty file."""
        x.upload_song(jukebox_connection, b"empty_song\n", b"")
        
        # Check that the program handles empty files appropriately
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_upload_non_wav_data(self, jukebox_connection):
        """Test uploading non-WAV data."""
        fake_data = b"This is not a WAV file" * 100
        x.upload_song(jukebox_connection, b"fake_song\n", fake_data)
        
        # Check that the program handles non-WAV data appropriately
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_upload_moderate_song_name(self, jukebox_connection):
        """Test uploading with a moderate length song name."""
        moderate_name = b"A" * 50 + b"\n"
        script_dir = os.path.dirname(os.path.abspath(__file__))
        with open(f"{script_dir}/data/test_simple.wav", "rb") as f:
            wav_data = f.read()
        
        x.upload_song(jukebox_connection, moderate_name, wav_data)
        
        # Check that the program handles moderate names appropriately
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_upload_medium_file(self, jukebox_connection):
        """Test uploading a medium-sized file."""
        medium_data = b"X" * 1000
        x.upload_song(jukebox_connection, b"medium_song\n", medium_data)
        
        # Check that the program handles medium files appropriately
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
    
    def test_multiple_uploads_same_connection(self, jukebox_connection):
        """Test uploading multiple songs with the same connection."""
        script_dir = os.path.dirname(os.path.abspath(__file__))
        with open(f"{script_dir}/data/test_8bit.wav", "rb") as f:
            wav_data = f.read()
        
        # Upload first song
        x.upload_song(jukebox_connection, b"song1\n", wav_data)
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
        
        # Upload second song
        x.upload_song(jukebox_connection, b"song2\n", wav_data)
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)

        # check listing
        x.list_songs(jukebox_connection)
        response = jukebox_connection.readuntil(b"=== jukebooox ===", timeout=5)
        assert b"song1" in response
        assert b"song2" in response
