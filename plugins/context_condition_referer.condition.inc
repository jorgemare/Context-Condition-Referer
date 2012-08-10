<?php

class context_condition_referer_context_referer extends context_condition {
  /**
   * Omit condition values. We will provide a custom input form for our conditions.
   */
  function condition_values() {
    return array();
  }

  /**
   * Condition form.
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    unset($form['#options']);

    $form['#type'] = 'textarea';
    $form['#default_value'] = implode("\n", $this->fetch_from_context($context, 'values'));
    return $form;
  }

  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    $parsed = array();
    $items = explode("\n", $values);
    if (!empty($items)) {
      foreach ($items as $v) {
        $v = trim($v);
        if (!empty($v)) {
          $parsed[$v] = $v;
        }
      }
    }
    return $parsed;
  }

    /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $paths = $this->fetch_from_context($context, 'values');
        if ($this->referer_match($paths)) {
          $this->condition_met($context);
        }
      }
    }
  }

  /**
   * Return TRUE if the $_SERVER['HTTP_REFERER'] matches a string in $paths
   *
   * @return [type] [description]
   */
  protected function referer_match($paths) {
    foreach ($paths as $path) {
      if (preg_match('#' . preg_quote($path) . '#', $_SERVER['HTTP_REFERER'])) {
        return TRUE;
      }
    }
  }
}
