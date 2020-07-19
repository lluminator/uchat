#include "../inc/uchat.h"

static void command_msg(t_user *us, t_add_m *s) {
    char *id = NULL;

    if (us->m->order == -2) {
        us->m->command = mx_arrjoin(us->m->command, "mx_add_new_user");
        us->m->command = mx_arrjoin(us->m->command, "User1");
        us->m->command = mx_arrjoin(us->m->command, "1");
        us->m->command = mx_arrjoin(us->m->command, "./User1.jpg");
        us->m->order = -1;
        return ;
    }
    if (us->m->order == -1) {
        us->m->command = mx_arrjoin(us->m->command, "mx_update");
        us->m->command = mx_arrjoin(us->m->command, "user");
        us->m->command = mx_arrjoin(us->m->command, "User1");
        us->m->order = 1;
        return ;
    }

    us->m->command = mx_arrjoin(us->m->command, "mx_recv_new_mssg");
    us->m->command = mx_arrjoin(us->m->command, us->m->my_name);
    us->m->command = mx_arrjoin(us->m->command, us->name);
    us->m->command = mx_arrjoin(us->m->command, s->text);
    us->m->command = mx_arrjoin(us->m->command, "0");
    us->m->command = mx_arrjoin(us->m->command, 
        s->forw == 1 ? s->forw_from : "NULL");
    if (s->reply_id != -1) {
        id = mx_itoa(s->reply_id);
        us->m->command = mx_arrjoin(us->m->command, id);
        free(id);
    }
    else 
        us->m->command = mx_arrjoin(us->m->command, "NULL");
}

static void add_time(t_user *i, t_add_m *s) {
    char **m = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    if (s->time_m == NULL) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        s->time_m = asctime(timeinfo);
        m = mx_strsplit(s->time_m, '\n');
        gtk_widget_set_tooltip_text(i->msg->next->label, m[0]);
        mx_del_strarr(&m);
    }
    else
        gtk_widget_set_tooltip_text(i->msg->next->label, s->time_m);
}

void add_message(t_user *i, t_add_m *s) {
    GtkWidget *wid;
    char *str = mx_strnew(mx_strlen(s->text) + ((mx_strlen(s->text)/50) + 1));
    int k = 0;

    for (int j = 0; s->text[j]; j++) {
        str[k++] = s->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    msg_pushfront(&i->msg, str, s->my, s->forw);
    gtk_grid_insert_row(GTK_GRID(i->m->grid_user), i->row++);
    i->msg->next->user = i;
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(wid, 650, 30);
    add_time(i, s);
    MX_MSG_PACK(s->my, i->msg->next->label, wid);
    gtk_grid_attach(GTK_GRID(i->text_grid), wid, 0, i->msg->next->count, 1, 1);
    gtk_widget_show_all(wid);
    i->msg->next->adj_value = gtk_adjustment_get_value(i->m->adj);
    reset_l_mess(i);
    free(str);
    command_msg(i, s);
    free(s);
}

void send_but(GtkWidget *wid, t_main *m) {
    char *text = NULL;
    t_add_m *s = NULL;

    text = (char *)gtk_entry_get_text(GTK_ENTRY(m->sms));
    if (text == NULL || !mx_strlen(text))
        return ;
    reset_users(m);
    s = create_struct(text, true, 0, NULL);
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true) 
            add_message(i, s);
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
    // m->order = 1;
    g_idle_add((GSourceFunc)move_scrol, m);
}
// Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
