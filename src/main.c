#include <assert.h>
#include <concord/discord.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void on_ready(struct discord *client) {
  const struct discord_user *bot = discord_get_self(client);
  log_info("Logged in as %s!", bot->username);

  struct discord_activity activities[] = {
      {
          .name = "with code",
          .type = DISCORD_ACTIVITY_GAME,
          .details = "Hopefully not breaking",
      },
  };

  struct discord_presence_update status = {
      .activities =
          &(struct discord_activities){
              .size = sizeof(activities) / sizeof *activities,
              .array = activities,
          },
      .status = "online",
      .afk = false,
      .since = discord_timestamp(client),
  };
  discord_set_presence(client, &status);
}

void lang(struct discord *client, const struct discord_message *msg) {
  if (msg->author->bot)
    return;

  char lang[1024];
  snprintf(lang, sizeof(lang), "commands/langs/%s.json", msg->content);
  size_t size = 0;
  char *json = cog_load_whole_file(lang, &size);
  struct discord_embed embed = {0};
  discord_embed_from_json(json, size, &embed);
  embed.color = 5793266;
  embed.timestamp = discord_timestamp(client);

  struct discord_create_message params = {0};
  params.embeds = &(struct discord_embeds){
      .size = 1,
      .array = &embed,
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_embed_cleanup(&embed);
  free(json);
}

void person(struct discord *client, const struct discord_message *msg) {
  if (msg->author->bot)
    return;

  char person[1024];
  snprintf(person, sizeof(person), "commands/people/%s.json", msg->content);
  size_t size = 0;
  char *json = cog_load_whole_file(person, &size);
  struct discord_embed embed = {0};
  discord_embed_from_json(json, size, &embed);
  embed.color = 5793266;
  embed.timestamp = discord_timestamp(client);

  struct discord_create_message params = {0};
  params.embeds = &(struct discord_embeds){
      .size = 1,
      .array = &embed,
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_embed_cleanup(&embed);
  free(json);
}

void framework(struct discord *client, const struct discord_message *msg) {
  if (msg->author->bot)
    return;

  char framework[1024];
  snprintf(framework, sizeof(framework), "commands/frameworks/%s.json",
           msg->content);
  size_t size = 0;
  char *json = cog_load_whole_file(framework, &size);
  struct discord_embed embed = {0};
  discord_embed_from_json(json, size, &embed);
  embed.color = 5793266;
  embed.timestamp = discord_timestamp(client);

  struct discord_create_message params = {0};
  params.embeds = &(struct discord_embeds){
      .size = 1,
      .array = &embed,
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_embed_cleanup(&embed);
  free(json);
}

void help(struct discord *client, const struct discord_message *msg) {
  if (msg->author->bot)
    return;

  size_t size = 0;
  char *json = cog_load_whole_file("commands/info/help.json", &size);
  struct discord_embed embed = {0};
  discord_embed_from_json(json, size, &embed);
  embed.color = 5793266;
  embed.timestamp = discord_timestamp(client);

  struct discord_create_message params = {0};
  params.embeds = &(struct discord_embeds){
      .size = 1,
      .array = &embed,
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_embed_cleanup(&embed);
  free(json);
}

int main(int argc, char *argv[]) {
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "config.json";

  ccord_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initizlize client");

  discord_set_on_ready(client, &on_ready);

  discord_set_prefix(client, ".");
  discord_set_on_command(client, "lang", &lang);
  discord_set_on_command(client, "l", &lang);
  discord_set_on_command(client, "person", &person);
  discord_set_on_command(client, "p", &person);
  discord_set_on_command(client, "framework", &framework);
  discord_set_on_command(client, "f", &framework);
  discord_set_on_command(client, "help", &help);

  discord_run(client);

  discord_cleanup(client);
  ccord_global_cleanup();
}
