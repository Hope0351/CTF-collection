const std = @import("std");
const util = @import("util.zig");
const crypto = @import("crypto.zig");
const cards = @import("cards.zig");
const server = @import("server.zig");
const game = @import("game.zig");
const ge = @import("ge.zig");

const String = util.String;
//
//
//
//

//noinline
pub fn main() !void {
    //var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    //var gpa = std.heap.c_allocator;

    const allocator = std.heap.c_allocator;

    // var card = cards.Card{ .id = 1, .power = 100 };

    //var card_manager = cards.CardManager{ .allocator = allocator };
    //var output = try card_manager.export_card(&card);
    //defer output.deinit();
    //util.puts_debug(output.data.items);

    //const line = try util.get_line_from_stdin(allocator);

    //_ = gpa.deinit();

    //try card_manager.import_card(line);

    //waitForEnter();

    try game.init(allocator);
    ge.init_engines();

    var game_server = try server.Server.init(allocator, "0.0.0.0", 8080);
    try game_server.listen();
}
