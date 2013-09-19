<?php

/**
 * @file
 * Page callbacks.
 */

/**
 *  Page callback to flag / unflag content.
 */
function flag_as_page($action, $flag_id, $content_id, $uid) {
  $flag = flag_get_flag(NULL, $flag_id);
  $account = user_load($uid);
  flag($action, $flag->name, $content_id, $account);
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 *
 * Return users:
 *  1.) Respect user roles
 *  2.) Not flagged users
  * 3.) TODO: users which own content
 */
function flag_as_autocomplete($flag_id, $content_id, $string = '') {
  $matches = array();
  if ($string) {
    // Get list of allowed roles for flag.
    $flag = flag_get_flag(NULL, $flag_id);
    $allowed_roles = $flag->roles['flag'];

    // Load users of role, which have not flagged the content.
    $query = db_select('users', 'u');
    $query->fields('u', array('name'));
    $query->condition('name', db_like($string) . '%', 'LIKE');
    // 1.) Respect user roles
    // DRUPAL_AUTHENTICATED_RID not actualy stored in users_roles table.
    // If user flag is allowed for authentificated users, other role check is irrelevant.
    if (!in_array(DRUPAL_AUTHENTICATED_RID, $allowed_roles)) {
      $query->join('users_roles', 'ur', 'u.uid = ur.uid');
      $query->condition('ur.rid', $allowed_roles, 'IN');
    }
    $query->range(0, 10);

    // 2.) Not flagged users
    $subquery = db_select('flag_content', 'fc')
      ->fields('fc', array('uid'))
      ->condition('content_id', $content_id)
      ->condition('fid', $flag_id);
    $query->condition('u.uid', $subquery, 'NOT IN');

    $result = $query->execute();
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json_output($matches);
}