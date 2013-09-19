<?php

/**
 * @file
 * Admin callbacks.
 */

function flag_as_settings_form($form, &$form_state) {
  $form = array();
  $flags = flag_get_flags('node');
  $flag_options = array();
  foreach ($flags as $flag) {
    if ($flag->global == 0) {
      // Listing only not global flags.
      $flag_options[$flag->fid] = $flag->title;
    }
  }
  $form['flag_as_op_flag_allowed'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Flag operation allowed to following flags'),
    '#default_value' => variable_get('flag_as_op_flag_allowed', array()),
    '#options' => $flag_options,
  );
  $form['flag_as_op_unflag_allowed'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Unflag operation allowed to following flags'),
    '#default_value' => variable_get('flag_as_op_unflag_allowed', array()),
    '#options' => $flag_options,
  );
  return system_settings_form($form);
}